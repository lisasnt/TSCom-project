import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.linear_model as lm
from scipy.stats import sem, t


file_path = "Measurments/test_v2.xlsx"
df = pd.read_excel(file_path, engine='openpyxl')
df_ultrasound = df[['ultrasound', 'real']]
df_ultrasound = df_ultrasound.dropna()
ultrasound_dict = df_ultrasound.groupby('real')['ultrasound'].apply(list).to_dict()

for key in ultrasound_dict:
    l = ultrasound_dict[key]
    ultrasound_dict[key] = [x - 1.6 for x in l]
    

'''
df_infrared_red = df[['red', 'real']]
df_infrared_red = df_infrared_red.dropna()
df_infrared_white = df[['white', 'real']]
df_infrared_white = df_infrared_white.dropna()
df_infrared_blue = df[['blue', 'real']]
df_infrared_blue = df_infrared_blue.dropna()

infrared_red_dict = df_infrared_red.groupby('real')['red'].apply(list).to_dict()
infrared_white_dict = df_infrared_white.groupby('real')['white'].apply(list).to_dict()
infrared_blue_dict = df_infrared_blue.groupby('real')['blue'].apply(list).to_dict()
'''
a = 90
white_list = np.array(df['white'].dropna().tolist())[0:a]
blue_list = np.array(df['blue'].dropna().tolist())[0:a]
red_list = np.array(df['red'].dropna().tolist())[0:a]
real_list = np.array(df['real'].dropna().tolist())[0:a]
white_transformed = [white_list,white_list**2,((1/(white_list+1.6)*1000)**2)]
white_transformed = np.array(white_transformed).T
blue_transformed = [blue_list,blue_list**2,((1/(blue_list+1.6)*1000)**2)]
blue_transformed = np.array(blue_transformed).T
red_transformed = [red_list,red_list**2,((1/(red_list+1.6)*1000)**2)]
red_transformed = np.array(red_transformed).T

infra_model = lm.LinearRegression()

infra_model.fit(white_transformed, real_list)
infra_pred_white = infra_model.predict(white_transformed)
print("White: ", infra_model.coef_)
print("White: ", infra_model.intercept_)

infra_model.fit(blue_transformed, real_list)
infra_pred_blue = infra_model.predict(blue_transformed)
print("Blue: ", infra_model.coef_)
print("Blue: ", infra_model.intercept_)

infra_model.fit(red_transformed, real_list)
infra_pred_red = infra_model.predict(red_transformed)
print("Red: ", infra_model.coef_)
print("Red: ", infra_model.intercept_)

def to_dict(values, measurements):
    result_dict = {}
    for value, measurement in zip(values, measurements):
        if value not in result_dict:
            result_dict[value] = []  # Initialize a list for new keys
        result_dict[value].append(measurement) 
    return result_dict

white_dict = to_dict(real_list, infra_pred_white)
blue_dict = to_dict(real_list, infra_pred_blue)
red_dict = to_dict(real_list, infra_pred_red)

confidence_level = 0.95
def conf_interval(data, confidence_level):

    means = []
    cis = []
    keys = []
    ses = []
    for value, measurements in data.items():
        keys.append(value)
        mean = np.mean(measurements)
        means.append(mean)

        se = sem(measurements)
        ses.append(se)
        df = len(measurements) - 1
        t_score = t.ppf((1 + confidence_level) / 2, df)
        ci = t_score * se
        cis.append(ci)
    return means, cis, keys, ses

means_ultrasound, cis_ultrasound, keys_ultrasound, se_ultrasound = conf_interval(ultrasound_dict, confidence_level)
means_infrared_white, cis_infrared_white, keys_infrared_white, se_infrared_white = conf_interval(white_dict, confidence_level)
means_infrared_red, cis_infrared_red, keys_infrared_red, se_infrared_red = conf_interval(red_dict, confidence_level)
means_infrared_blue, cis_infrared_blue, keys_infrared_blue, se_infrared_blue = conf_interval(blue_dict, confidence_level)   
        
plt.figure(figsize=(8, 6))
plt.title('Measurements with Mean and Confidence Intervals')
plt.xlabel('Real Value')
plt.ylabel('Measurement')
plt.grid(True, linestyle='--', alpha=0.7)


plt.errorbar(keys_ultrasound, means_ultrasound, yerr=cis_ultrasound, fmt='o', capsize=5, label='Ultrasound: Mean ± CI', color='green')
plt.errorbar(keys_infrared_red, means_infrared_red, yerr=cis_infrared_red, fmt='o', capsize=5, label='Infrared Red: Mean ± CI', color='red')
plt.errorbar(keys_infrared_white, means_infrared_white, yerr=cis_infrared_white, fmt='o', capsize=5, label='Infrared White: Mean ± CI', color='blue')
plt.errorbar(keys_infrared_blue, means_infrared_blue, yerr=cis_infrared_blue, fmt='o', capsize=5, label='Infrared Blue: Mean ± CI', color='purple')

x = np.linspace(0, 100, 100)
y = x
plt.plot(x, y, 'k--', label='y=x')

plt.legend()
plt.show()



plt.plot(white_list, infra_pred_white, label='Infra Red White')
plt.scatter(white_list, real_list, label='Real')


plt.plot(blue_list, infra_pred_blue, label='Infra Red Blue')
plt.scatter(blue_list, real_list, label='Real')


plt.plot(red_list, infra_pred_red, label='Infra Red Red')
plt.scatter(red_list, real_list, label='Real')
plt.legend()
plt.show()
    

'''
#Do this for each coulmn
valid_data = df['A'].dropna().tolist()

#Infrared
infra_model = lm.LinearRegression()

XW_green = [infra_red_green,((1/(infra_red_green+1.6)*1000)**2)]
XW_green = np.array(XW_green).T
infra_model.fit(XW_green, real_distance_green)
infra_pred_green = infra_model.predict(XW_green)

XW_white = [infra_red_white,((1/(infra_red_white+1.6)*1000)**2)]
XW_white = np.array(XW_white).T
infra_model.fit(XW_white, real_distance_white)
infra_pred_white = infra_model.predict(XW_white)

XW_black = [infra_red_black,((1/(infra_red_black+1.6)*1000)**2)]
XW_black = np.array(XW_black).T
infra_model.fit(XW_black, real_distance_black)
infra_pred_black = infra_model.predict(XW_black)




#ultrasonic
ultra_model = lm.LinearRegression()
ultra_model.fit(ultra_sound, real_distance)
ultra_pred = ultra_model.predict(ultra_sound)
ultra_error = (real_distance - ultra_pred)**2


print(df)
df = df.dropna(how='all').reset_index(drop=True)
print(df)
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
 


infra_model = lm.LinearRegression()
XW_green = [infra_red_green,((1/(infra_red_green+1.6)*1000)**2)]
XW_green = np.array(XW_green).T
infra_model.fit(XW_green, real_distance_green)
infra_pred_green = infra_model.predict(XW_green)
infra_error_green = (real_distance_green - infra_pred_green)**2

XW_white = [infra_red_white,((1/(infra_red_white+1.6)*1000)**2)]
XW_white = np.array(XW_white).T
infra_model.fit(XW_white, real_distance_white)
infra_pred_white = infra_model.predict(XW_white)
infra_error_white = (real_distance_white - infra_pred_white)**2

XW_black = [infra_red_black,((1/(infra_red_black+1.6)*1000)**2)]
XW_black = np.array(XW_black).T
infra_model.fit(XW_black, real_distance_black)
infra_pred_black = infra_model.predict(XW_black)
infra_error_black = (real_distance_black - infra_pred_black)**2

plt.plot(real_distance, ultra_sound, 'ro', label='Ultra Sound')
plt.plot(real_distance_green, infra_pred_green, 'go', label='Infra Red Green')
plt.plot(real_distance_white, infra_pred_white, 'bo', label='Infra Red White')
plt.plot(real_distance_black, infra_pred_black, 'yo', label='Infra Red Black')
plt.xlabel('Real Distance')
plt.ylabel('Sensor Reading')
plt.legend()
plt.show()  


plt.plot(real_distance, ultra_pred, 'ro', label='Ultra Sound')
plt.plot(real_distance_white, infra_error_white, 'bo', label='Infra Red White')
plt.plot(real_distance_green, infra_error_green, 'go', label='Infra Red Green')
plt.plot(real_distance_black, infra_error_black, 'yo', label='Infra Red Black')
plt.xlabel('Real Distance')
plt.ylabel('Error')
plt.legend()
plt.show()


def get_error(real_distance, pred_distance):
    for i in range(len(real_distance)):
        np.coun
        real_distance_i = real_distance[i]
        for j in range(i*5, i*5+5):
            print(j)
            errors = np.append(errors, (real_distance_i - pred_distance[j])**2)             
    return errors

print(get_error(real_distance, ultra_pred))
'''







