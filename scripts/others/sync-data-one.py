import sys
import pandas as pd
import numpy as np

# Check for arguments
if len(sys.argv) < 3:
    print("Usage: python script.py <folder> <sequence_number>")
    sys.exit(1)

# Get arguments
folder = sys.argv[1]
seq = sys.argv[2]  # Now taken from command line

# Read ARKit data
path = f'{folder}/advio-{seq}/iphone/arkit.csv'
arkit = pd.read_csv(path, names=list('tabcdefg'))

# Read accelerometer data
path = f'{folder}/advio-{seq}/iphone/accelerometer.csv'
acc = pd.read_csv(path, names=list('tabc'))

# Read gyroscope data
path = f'{folder}/advio-{seq}/iphone/gyro.csv'
gyro = pd.read_csv(path, names=list('tabc'))

# Extract gyroscope timestamps
t = np.array(gyro['t'].astype(float))
zer = t * 0.0

# Interpolate accelerometer data to gyroscope timestamps
a = []
g = []
for c in 'abc':
    a.append(np.interp(t, acc['t'].astype(float), acc[c].astype(float)))
    g.append(gyro[c].astype(float).values)

# Compose IMU data matrix
M = np.column_stack((t, zer + 34, g[0], g[1], g[2], a[0], a[1], a[2], zer, zer))

# Process ARKit data
v = []
t_arkit = arkit['t'].astype(float).values
t_arkit -= t_arkit[0]
zer_arkit = t_arkit * 0
for c in 'abcdefg':
    v.append(arkit[c].astype(float).values)

# Compose ARKit data matrix
Mkit = np.column_stack((t_arkit, zer_arkit + 7, np.arange(len(zer_arkit)), *v))

# Concatenate and sort all data by time
full = np.concatenate((M, Mkit))
full = full[full[:, 0].argsort()]

# Save output
output_path = f'{folder}/advio-{seq}/iphone/imu-gyro.csv'
np.savetxt(output_path, full, delimiter=",", fmt='%.6f')

