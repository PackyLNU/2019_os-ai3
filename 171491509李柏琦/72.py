import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.naive_bayes import GaussianNB
from sklearn.datasets import load_iris

#打印数据集的关键值
iris = load_iris()
print('\n\n\n')
print('代码运行结果为：')
print("==================================================\n")
print(iris.keys())
print("\n==================================================")
print('\n\n\n')

#打印数据集中标注好的分类
n_samples, n_features = iris.data.shape

print("\n==================================================")
print("样本的数量和特征向量的维数：")
print((n_samples, n_features))
print("\n==================================================")
print("数据0的特征值：")
print(iris.data[0])
print("\n==================================================")
print("target的分类数：")
print(iris.target.shape)
print("\n==================================================")
print("target的数据：")
print(iris.target)
print("\n==================================================")
print("鸢尾花的类：")
print(iris.target_names)
print("\n==================================================")
print("特征向量的名称：")
print("feature_names:",iris.feature_names)
print("\n==================================================")




# 生成所有测试样本点
def make_meshgrid(x, y, h=.02):
    x_min, x_max = x.min() - 1, x.max() + 1
    y_min, y_max = y.min() - 1, y.max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
    np.arange(y_min, y_max, h))
    return xx, yy

# 对测试样本进行预测，并显示
def plot_test_results(ax, clf, xx, yy, **params):
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    ax.contourf(xx, yy, Z, **params)

# 载入iris数据集
iris = datasets.load_iris()
# 只使用前面连个特征
X = iris.data[:, :2]
# 样本标签值
y = iris.target

# 创建并训练正态朴素贝叶斯分类器
clf = GaussianNB()
clf.fit(X,y)

title = ('GaussianBayesClassifier')

fig, ax = plt.subplots(figsize = (5, 5))
plt.subplots_adjust(wspace=0.4, hspace=0.4)

X0, X1 = X[:, 0], X[:, 1]
# 生成所有测试样本点
xx, yy = make_meshgrid(X0, X1)

# 显示测试样本的分类结果
plot_test_results(ax, clf, xx, yy, cmap=plt.cm.coolwarm, alpha=0.8)
# 显示训练样本
ax.scatter(X0, X1, c=y, cmap=plt.cm.coolwarm, s=20, edgecolors='k')
ax.set_xlim(xx.min(), xx.max())
ax.set_ylim(yy.min(), yy.max())
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_xticks(())
ax.set_yticks(())
ax.set_title(title)
plt.show()