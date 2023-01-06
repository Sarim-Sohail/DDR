using System;
using System.Collections.Generic;
using System.Threading;

class Scheduler {
  private readonly Timer timer;
  private readonly Dictionary<Action, int> tasks;

  public Scheduler() {
    tasks = new Dictionary<Action, int>();
    timer = new Timer(Tick, null, Timeout.Infinite, Timeout.Infinite);
  }

  public void AddTask(Action task, int interval) {
    tasks[task] = interval;
    timer.Change(0, Timeout.Infinite);
  }

  public void RemoveTask(Action task) {
    tasks.Remove(task);
  }

  private void Tick(object state) {
    var now = DateTime.Now;
    foreach (var task in tasks) {
      if (now.Ticks % task.Value == 0) {
        task.Key();
      }
    }
    timer.Change(1000, Timeout.Infinite);
  }
}

class Program {
  static void Main() {
    var scheduler = new Scheduler();

    // Add a task that prints "Hello, world!" every 2 seconds
    scheduler.AddTask(() => Console.WriteLine("Hello, world!"), 2000);

    // Wait for 10 seconds
    Thread.Sleep(10000);
  }
}