# 死区时间计算方法
# Tdts=1/180M (定时器时钟频率)
# DTG[7:5]=0xx, DT=DTG[7:0]*Tdgt,      Tdgt=Tdts
# DTG[7:5]=10x, DT=(64+DTG[5:0])*Tdgt, Tdgt=2*Tdts
# DTG[7:5]=101, DT=(32+DTG[4:0])*Tdgt, Tdgt=8*Tdts
# DTG[7:5]=111, DT=(32+DTG[4:0])*Tdgt, Tdgt=16*Tdts

sys_clk = 180


def time_to_dt(x):
    dt = -1
    if 0 <= x < 0b10000000:
        dt = x
    elif x < 0b10100000:
        dt = (x & 0b111111) + 64
        dt = dt * 2
    elif x < 0b11100000:
        dt = (x & 0b11111) + 32
        dt = dt * 8
    elif x <= 0b11111111:
        dt = (x & 0b11111) + 32
        dt = dt * 16
    return dt, dt / sys_clk


print("DTG[7:0],DT/Tdts,DT")
for i in range(0, 256):
    print("{},{},{:.2f}us".format(i, time_to_dt(i)[0], time_to_dt(i)[1]))
