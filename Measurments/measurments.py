import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.linear_model as lm

file_path = "Data.xlsx"
df = pd.read_excel(file_path)

df = df.dropna(how='all').reset_index(drop=True)

#White
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
 
#concatenate the data
ultra_sound = ultra_sound_white + ultra_sound_green + ultra_sound_black
ultra_sound = np.array(ultra_sound).reshape(-1, 1)
real_distance = np.array(real_distance_white + real_distance_green + real_distance_black)
   
#Remove NAN values
infra_red_green = infra_red_green[~np.isnan(real_distance_green)]
infra_red_white = infra_red_white[~np.isnan(real_distance_white)]
infra_red_black = infra_red_black[~np.isnan(real_distance_black)]
real_distance_green = real_distance_green[~np.isnan(real_distance_green)]
real_distance_white = real_distance_white[~np.isnan(real_distance_white)]
real_distance_black = real_distance_black[~np.isnan(real_distance_black)]
ultra_sound = ultra_sound[~np.isnan(real_distance)]
real_distance = real_distance[~np.isnan(real_distance)]
 
ultra_model = lm.LinearRegression()
ultra_model.fit(ultra_sound, real_distance)
ultra_pred = ultra_model.predict(ultra_sound)
ultra_error = abs(ultra_pred - real_distance)

infra_model = lm.LinearRegression()
XW_green = [infra_red_green,((1/(infra_red_green+1.6)*1000)**2)]
XW_green = np.array(XW_green).T
infra_model.fit(XW_green, real_distance_green)
infra_pred_green = infra_model.predict(XW_green)
print(ultra_sound)
infra_error_green = abs(infra_pred_green - real_distance_green)

XW_white = [infra_red_white,((1/(infra_red_white+1.6)*1000)**2)]
XW_white = np.array(XW_white).T
infra_model.fit(XW_white, real_distance_white)
infra_pred_white = infra_model.predict(XW_white)
infra_error_white = abs(infra_pred_white - real_distance_white)

XW_black = [infra_red_black,((1/(infra_red_black+1.6)*1000)**2)]
XW_black = np.array(XW_black).T
infra_model.fit(XW_black, real_distance_black)
infra_pred_black = infra_model.predict(XW_black)
infra_error_black = abs(infra_pred_black - real_distance_black)

plt.plot(real_distance, ultra_pred, 'ro', label='Ultra Sound')
plt.plot(real_distance_white, infra_error_white, 'bo', label='Infra Red White')
plt.plot(real_distance_green, infra_error_green, 'go', label='Infra Red Green')
plt.plot(real_distance_black, infra_error_black, 'yo', label='Infra Red Black')
plt.xlabel('Real Distance')
plt.ylabel('Error')
plt.legend()
plt.show()









