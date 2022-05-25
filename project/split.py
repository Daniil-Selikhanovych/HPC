with open("core_logs.log") as f:
	lines = f.readlines()
	n = len(lines)
	n //= 2
	for i in range(n, len(lines)):
		print(lines[i])
