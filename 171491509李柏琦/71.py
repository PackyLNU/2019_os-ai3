#打印肿瘤数据集的键值
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split#用model_selection模块导入train_test_split
from sklearn.naive_bayes import GaussianNB#调用高斯贝叶斯
from sklearn.model_selection import ShuffleSplit
from matplotlib import pyplot as plt
import numpy as np
from sklearn.model_selection import learning_curve
fig = plt.figure()

cancer = load_breast_cancer()
print('\n\n\n')
print('代码运行结果为：')
print("==================================================\n")
print(cancer.keys())
print("\n==================================================")
print('\n\n\n')

#打印数据集中标注好的肿瘤分类
print("肿瘤的分类：",cancer["target_names"])
#打印数据集中的肿瘤特征名称
print("\n肿瘤的特征：",cancer["feature_names"])

#将数据集中的数值和分类目标分别赋值给x和y
X,y = cancer.data,cancer.target
#使用数据集拆分工具拆分为训练集和测试集
X_train,X_test,y_train,y_test = train_test_split(X,y,random_state=38)
print("\n\n\n")
print("代码运行结果：")
print("==================================================\n")
#打印训练集和测试集的数据状态
print("训练集数据状态：",X_train.shape)
print("测试集数据状态：",X_test.shape)
print("\n==================================================")
print("\n\n\n")

#使用高斯朴素贝叶斯拟合数据
gnb = GaussianNB()
gnb.fit(X_train,y_train)
print("\n\n\n")
print("代码运行结果：")
print("==================================================\n")
#打印模型评分
print("训练集得分：{:.3f}".format(gnb.score(X_train,y_train)))
print("测试集得分：{:.3f}".format(gnb.score(X_test,y_test)))
print("\n==================================================")
print("\n\n\n")

#随便使用一个模型进行预测
print("\n\n\n")
print("代码运行结果：")
print("==================================================\n")
#打印模型预测的分类和真实的分类
print("模型预测的分类是：{}".format(gnb.predict([X[312]])))
print("样本的正确分类是：",y[312])
print("\n==================================================")
print("\n\n\n")

#定义一个函数绘制学习曲线
def plot_learning_curve(estimator,title,X,y,ylim=None,cv=None,
                        n_jobs=1,train_sizes=np.linspace(.1,1.0,5)):
    plt.figure()
    plt.title(title)
    if ylim is not None:
        plt.ylim(*ylim)

#设定横轴标签
    plt.xlabel("Training examples")
#设定纵轴标签
    plt.ylabel("Score")
    train_sizes,train_scores,test_scores = learning_curve(
        estimator,X,y,cv=cv,n_jobs=n_jobs,train_sizes=train_sizes
    )
    train_scores_mean = np.mean(train_scores,axis=1)
    test_scores_mean = np.mean(test_scores,axis=1)
    plt.plot(train_sizes,train_scores_mean,'o-',color="r",
             label="Training score")
    plt.plot(train_sizes,test_scores_mean,'o-',color="g",
             label="Cross-validation score")
    plt.legend(loc="lower right")
    return plt
#设定图题
title = "Learning Curves (Naive Bayes)"
#设定拆分量
cv = ShuffleSplit(n_splits=100,test_size=0.2,random_state=0)
#设定模型为高斯朴素贝叶斯
estimator = GaussianNB()
#调用定义好的函数
plot_learning_curve(estimator,title,X,y,ylim=(0.9,1.01),cv=cv,n_jobs=4)
#显示图片
plt.show()