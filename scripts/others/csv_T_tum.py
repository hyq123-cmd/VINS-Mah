import sys
import pandas as pd

# 检查命令行参数
if len(sys.argv) != 3:
    print("用法: python convert_to_tum.py input.csv output.txt")
    sys.exit(1)

input_path = sys.argv[1]
output_path = sys.argv[2]

# 读取 CSV 文件（假设无表头）
df = pd.read_csv(input_path, header=None)

# 确保只有前8列：timestamp, x, y, z, qx, qy, qz, qw
df = df.iloc[:, :8]

# 转换为 float 类型（清洗非法字符或空值）
df = df.apply(pd.to_numeric, errors='coerce')
df = df.dropna()  # 删除有 NaN 的行（例如含 #####）

# 保存为 TUM 格式：空格分隔，8列
df.to_csv(output_path, sep=' ', header=False, index=False, float_format='%.9f')

