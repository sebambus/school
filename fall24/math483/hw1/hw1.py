import numpy as np
import matplotlib.pyplot as pl
import pandas as pd

# Reading data
breast_data = np.load('breast_data.npy')
breast_labels = np.load('breast_labels.npy')
column_names = np.load('column_names.npy')

# Mapping breast_labels to strings
labels = {0:'Benign', 1:'Malignant'}

# Assembling data
df = pd.DataFrame(breast_data, columns=column_names)
df["breast labels"] = [labels[i] for i in breast_labels]

# Split data frame
gk = df.groupby('breast labels').groups
benigndf = df.iloc[gk['Benign']]
malignantdf = df.iloc[gk['Malignant']]

# Drop redundant columns
del benigndf['breast labels']
del malignantdf['breast labels']

# Print a summary of values for benign tumors
print("VALUES FOR BENIGN TUMORS")
for name,values in benigndf.items():
    print(name)
    print("Max:", max(values))
    print("Min:", min(values))
    print("Average:", sum(values)/len(values), "\n")

# Print a summary of values for benign tumors
print("VALUES FOR MALIGNANT TUMORS")
for name,values in malignantdf.items():
    print(name)
    print("Max:", max(values))
    print("Min:", min(values))
    print("Average:", sum(values)/len(values), "\n")

# Creates a scatterplot of the mean area and texture of tumors
pl.plot(benigndf["mean area"], benigndf["mean texture"], 'o', label="Benign")
pl.plot(malignantdf["mean area"], malignantdf["mean texture"], 'o', label="Malignant")
pl.xlabel("Mean Area")
pl.ylabel("Mean Texture")
pl.title("Area and Texture of Tumors")
pl.legend()
pl.show()

# Creates a histogram comparing mean area of malignant and benign tumors
pl.hist([malignantdf["mean area"], benigndf["mean area"]], bins=25, label=["Malignant", "Benign"])
pl.xlabel("Mean Area")
pl.title("Histogram of the Mean Area of Tumors")
pl.legend()
pl.show()

# Creates a histogram comparing mean texture of malignant and benign tumors
pl.hist([malignantdf["mean texture"], benigndf["mean texture"]], bins=25, label=["Malignant", "Benign"])
pl.xlabel("Mean Texture")
pl.title("Histogram of the Mean Texture of Tumors")
pl.legend()
pl.show()