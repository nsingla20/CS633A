import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv("data.csv")

df.drop(["source","destination"],axis=1,inplace=True)
df = df.astype({'size':'int','time':'float64'})
# df['time']/=1000000
plt.scatter(df['size'],df['time'],alpha=0.5)
df = df.groupby('size')['time'].apply(np.hstack).to_frame().reset_index()


xs=df['size']
ys=df['time'].apply(lambda x: x.mean())
yerr=[ys-df['time'].apply(lambda x: x.min()),df['time'].apply(lambda x: x.max())-ys]
# print(yerr)

plt.plot(xs,ys)
plt.errorbar(xs,ys,yerr=yerr,fmt ='o')
plt.xlabel("Size(Bytes)")
plt.ylabel("Time(s)")
plt.savefig("plot.png")
