import time

class Scheduler:
    def __init__(self):
        self.tasks = []

    def add_task(self, task, interval):
        self.tasks.append((task, interval))

    def run(self):
        while True:
            for task, interval in self.tasks:
                task()
                time.sleep(interval)

# Example usage
def say_hello():
    print("Hello!")

scheduler = Scheduler()
scheduler.add_task(say_hello, interval=5)
scheduler.run()