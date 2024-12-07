import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras.models import load_model
from tensorflow.keras.datasets import mnist
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay

#Load the MNIST dataset
(x_train, y_train), (x_test, y_test) = mnist.load_data()

#Add padding
x_test = np.pad(x_test, ((0, 0), (2, 2), (2, 2)), mode='constant')

#Scale the data
x_test = np.expand_dims(x_test, -1).astype('float32') / 255

#Load the trained model
model = load_model('lenet5_mnist.keras')

#Evaluate the model on the test set
loss, accuracy = model.evaluate(x_test, y_test)
print(f"Test Loss: {loss}")
print(f"Test Accuracy: {accuracy}")

#Plotting the confusion matrix
predictions = model.predict(x_test)
predictions = predictions.argmax(axis=1)
y_true = y_test

cm = confusion_matrix(y_true, predictions)
disp = ConfusionMatrixDisplay(confusion_matrix=cm)
disp.plot()
plt.show()
