from sklearn import linear_model
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_path = "Data.xlsx"
df = pd.read_excel(file_path)

df = df.dropna(how='all').reset_index(drop=True)

def fitData(x,X,y,cfg):
    Xi = np.transpose(X)
    model = cfg.fit(Xi,y)
    print(model.score(Xi,y))
    predi = model.predict(Xi)
    plt.scatter(x,y)
    plt.plot(x,predi)
    print(model.coef_)

ultra_sound_white = np.array(df.iloc[:, 0].tolist())
infra_red_white = np.array(df.iloc[:, 1].tolist())
real_distance_white = np.array(df.iloc[:, 2].tolist())

#Green
ultra_sound_green = np.array(df.iloc[:, 3].tolist())
infra_red_green = np.array(df.iloc[:, 4].tolist())
real_distance_green = np.array(df.iloc[:, 5].tolist())

#Black
ultra_sound_black = np.array(df.iloc[:, 6].tolist())
infra_red_black = np.array(df.iloc[:, 7].tolist())
real_distance_black = np.array(df.iloc[:, 8].tolist())

infra_red = infra_red_green[~np.isnan(real_distance_green)]
real_distance = real_distance_green[~np.isnan(real_distance_green)]

cfg = linear_model.LinearRegression()
XW = [infra_red,((1/(infra_red+1.6)*1000)**2)]



fitData(infra_red,XW,real_distance,cfg)

#plt.scatter(infra_red_white, real_distance_white, label='First')
#plt.scatter(infra_red_green, real_distance_green, label='Second')
#plt.scatter(infra_red_black, real_distance_black, label='Third')
plt.legend()
plt.show()
