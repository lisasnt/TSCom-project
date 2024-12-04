from sklearn import linear_model
import numpy as np
from matplotlib import pyplot as plt

xu = np.load("ultrasound.npy")
xi = np.load("infrared.npy")
y = np.load("distance.npy")
print(xu.shape)
print(xi.shape)
print(y.shape)

cfg = linear_model.LinearRegression()
X = np.transpose((xu,xi))

#Xi = np.transpose((xi, 1/(xi/1000)**2))
Xi2 = np.exp(-xi/1000)
model = cfg.fit(Xi2,y)
print(model.score(Xi,y))
predi = model.predict(Xi)
plt.scatter(y,xi)
plt.plot(y,xi)
model.coef_