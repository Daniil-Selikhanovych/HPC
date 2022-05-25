import numpy as np
file_names = ["core_logs_runtime.log", "core_not_parallel_logs_runtime.log"]
modes = ["parallel", "not parallel"]
for i in range(2):
    times = []
    with open(file_names[i]) as f:
        lines = f.readlines()
        for line in lines:
            time = float(line.split(" ")[-2])
            times.append(time)

    times = np.array(times)
    mean = np.mean(times)
    std = np.std(times)
    print(f"Computation mode = {modes[i]}, mean time = {round(mean, 3)}s, std time = {round(std, 3)}s")
