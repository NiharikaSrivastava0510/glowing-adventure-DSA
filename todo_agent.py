"""
Basic AI Agent for To-Do List Management
Uses natural language to add, complete, delete, and view tasks.
"""

import json
import os
from datetime import datetime

TODO_FILE = "todos.json"


def load_todos():
    """Load todos from file."""
    if os.path.exists(TODO_FILE):
        with open(TODO_FILE, "r") as f:
            return json.load(f)
    return []


def save_todos(todos):
    """Save todos to file."""
    with open(TODO_FILE, "w") as f:
        json.dump(todos, f, indent=2)


def add_task(todos, task_text, priority="medium"):
    """Add a new task."""
    task = {
        "id": len(todos) + 1,
        "task": task_text,
        "priority": priority,
        "done": False,
        "created": datetime.now().strftime("%Y-%m-%d %H:%M"),
    }
    todos.append(task)
    save_todos(todos)
    return f"Added: '{task_text}' (priority: {priority})"


def complete_task(todos, task_id):
    """Mark a task as done."""
    for task in todos:
        if task["id"] == task_id:
            task["done"] = True
            save_todos(todos)
            return f"Completed: '{task['task']}'"
    return f"Task #{task_id} not found."


def delete_task(todos, task_id):
    """Delete a task."""
    for i, task in enumerate(todos):
        if task["id"] == task_id:
            removed = todos.pop(i)
            save_todos(todos)
            return f"Deleted: '{removed['task']}'"
    return f"Task #{task_id} not found."


def show_tasks(todos, show_all=False):
    """Display tasks."""
    if not todos:
        return "No tasks yet! Add one with: add <task>"

    lines = ["\n--- Your To-Do List ---"]
    for task in todos:
        if not show_all and task["done"]:
            continue
        status = "[x]" if task["done"] else "[ ]"
        priority_icon = {"high": "!!!", "medium": "!!", "low": "!"}.get(task["priority"], "!!")
        lines.append(f"  {status} #{task['id']} {task['task']}  ({priority_icon} {task['priority']})")

    if len(lines) == 1:
        return "All tasks completed! Great job!"
    return "\n".join(lines)


def parse_command(user_input, todos):
    """AI-like parser: understands natural language commands."""
    text = user_input.strip().lower()

    # Show tasks
    if text in ("show", "list", "tasks", "view", "all", "show all"):
        show_all = "all" in text
        return show_tasks(todos, show_all=show_all)

    # Add task
    if text.startswith(("add ", "create ", "new ", "todo ")):
        # Extract priority if mentioned
        priority = "medium"
        task_text = user_input.strip()
        for prefix in ("add ", "create ", "new ", "todo "):
            if text.startswith(prefix):
                task_text = user_input.strip()[len(prefix):]
                break

        for p in ("high", "low", "medium"):
            if f"priority {p}" in text or f"!{p}" in text:
                priority = p
                task_text = task_text.replace(f"priority {p}", "").replace(f"!{p}", "").strip()

        return add_task(todos, task_text, priority)

    # Complete task
    if text.startswith(("done ", "complete ", "finish ", "check ")):
        try:
            task_id = int("".join(filter(str.isdigit, text)))
            return complete_task(todos, task_id)
        except ValueError:
            return "Please specify a task number. Example: done 1"

    # Delete task
    if text.startswith(("delete ", "remove ", "drop ")):
        try:
            task_id = int("".join(filter(str.isdigit, text)))
            return delete_task(todos, task_id)
        except ValueError:
            return "Please specify a task number. Example: delete 1"

    # Help
    if text in ("help", "?", "h"):
        return """
--- To-Do Agent Commands ---
  add <task>              Add a new task (e.g., add Buy groceries)
  add <task> priority high  Add with priority (high/medium/low)
  show / list             Show pending tasks
  show all                Show all tasks including completed
  done <id>               Mark task as completed
  delete <id>             Delete a task
  help                    Show this help
  quit                    Exit the agent
"""

    # Quit
    if text in ("quit", "exit", "bye", "q"):
        save_todos(todos)
        return "EXIT"

    return f"I didn't understand '{user_input}'. Type 'help' for available commands."


def main():
    print("=" * 40)
    print("   AI To-Do List Agent")
    print("=" * 40)
    print("Type 'help' for commands or just start adding tasks!\n")

    todos = load_todos()

    while True:
        try:
            user_input = input("You > ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nGoodbye!")
            break

        if not user_input:
            continue

        result = parse_command(user_input, todos)

        if result == "EXIT":
            print("Goodbye! Your tasks are saved.")
            break

        print(f"Agent > {result}\n")


if __name__ == "__main__":
    main()
