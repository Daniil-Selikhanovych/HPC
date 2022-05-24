f = open("/mnt/d/Common/HPC/molecular_dynamics/my_md.log").readlines()
n = len(f)
n //= 2
for i in range(n, len(f)): 
	print(f[i])
