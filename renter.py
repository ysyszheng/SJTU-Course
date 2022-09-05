import pandas as pd
import numpy as np

data = pd.read_stata(r'../data/main.dta')
data[['inc']] = data[['inc']].apply(pd.to_numeric, errors='coerce')
owner_data = data[data["belong"]=="Owner"]

with open("renter.do","w") as f:
  f.truncate()

# find the house price of the individual closest to its income
for i in range(len(data)):
  if data.loc[i,"belong"]=="Owner":
    continue
  inc = data.loc[i,"inc"]
  year = data.loc[i,"year"]
  provcd = data.loc[i,"provcd"]
  tmp_data = owner_data[owner_data['year']==year]
  tmp_data = tmp_data[tmp_data['provcd']==provcd]
  tmp_data_inc = tmp_data['inc']
  idx = (tmp_data_inc-inc).abs().argsort()
  tmp_data = tmp_data.iloc[idx[:1]]
  hp = np.median(tmp_data['hp'])
  with open("renter.do","a") as f:
      f.write("replace hp = " + str(hp) + " if fid==" + str(np.int64(data.loc[i,'fid'])) + "&year==" + str(np.int64(data.loc[i,'year'])) + '\n')
