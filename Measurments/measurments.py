import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.linear_model as lm
from scipy.stats import sem, t


file_path = "Measurments/Data.xlsx"
df = pd.read_excel(file_path, engine='openpyxl')
df_ultrasound = df[['ultrasound', 'real']]
df_ultrasound = df_ultrasound.dropna()
ultrasound_dict = df_ultrasound.groupby('real')['ultrasound'].apply(list).to_dict()

for key in ultrasound_dict:
    l = ultrasound_dict[key]
    ultrasound_dict[key] = [x - 1.6 for x in l]
    
a = 90
white_list = np.array(df['white'].dropna().tolist())[0:a]
blue_list = np.array(df['blue'].dropna().tolist())[0:a]
red_list = np.array(df['red'].dropna().tolist())[0:a]
real_list = np.array(df['real'].dropna().tolist())[0:a]
white_transformed = [white_list,white_list**2,((1/(white_list)*1000)**2)]
white_transformed = np.array(white_transformed).T
blue_transformed = [blue_list,blue_list**2,((1/(blue_list)*1000)**2)]
blue_transformed = np.array(blue_transformed).T
red_transformed = [red_list,red_list**2,((1/(red_list)*1000)**2)]
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
plt.plot(x, y, 'k--', label='y=x (Ideal Line)')

plt.legend()
plt.show()



plt.plot(white_list, infra_pred_white, label='Infra Red White')
plt.scatter(white_list, real_list, label='Real')


plt.plot(blue_list, infra_pred_blue, label='Infra Red Blue')
plt.scatter(blue_list, real_list, label='Real')
x = np.linspace(200, 1000, 100)
y = 1.58796880e-02 * x + -1.09140410e-05 * x**2 + 6.42136562e-01 * (1 / (x + 1.6) * 1000)** 2 - 5.55773930575693

plt.plot(x, y, 'k--', label='Regression Line')

plt.plot(red_list, infra_pred_red, label='Infra Red Red')
plt.scatter(red_list, real_list, label='Real')
plt.legend()
plt.show()