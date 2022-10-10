from matplotlib import pyplot as plt

# UNCOMMENT FIRST THE LINES IN BloomFilter.hh AND BloomFilter.cc WHERE h1, h2, ..., h6 APPEAR
# APPEARING IN FUNCTIONS Bloom, addWord AND IN THE CLASS Bloom
# DOING SO WILL GENERATE FILES h1 TO h6

n_bins = 50

plt.style.use('fivethirtyeight')

hash1 = []
hash2 = []
hash3 = []
hash4 = []
hash5 = []
hash6 = []

plt.rc('font', size=10) #controls default text size

f1 = open("h1", "r")
l1 = f1.readlines()

f2 = open("h2", "r")
l2 = f2.readlines()

f3 = open("h3", "r")
l3 = f3.readlines()

f4 = open("h4", "r")
l4 = f4.readlines()

f5 = open("h5", "r")
l5 = f5.readlines()

f6 = open("h6", "r")
l6 = f6.readlines()

for line in l1:
    hash1.append(int(line))

for line in l2:
    hash2.append(int(line))

for line in l3:
    hash3.append(int(line))

for line in l4:
    hash4.append(int(line))

for line in l5:
    hash5.append(int(line))

for line in l6:
    hash6.append(int(line))

figure, axis = plt.subplots(2, 3)

axis[0, 0].hist(hash1, bins=n_bins, edgecolor='black', color='red')
axis[0, 0].set_title("HASH 1")
axis[0, 0].get_xaxis().set_visible(False)
axis[0, 0].get_yaxis().set_visible(False)

axis[0, 1].hist(hash2, bins=n_bins, edgecolor='black', color='orange')
axis[0, 1].set_title("HASH 2")
axis[0, 1].get_xaxis().set_visible(False)
axis[0, 1].get_yaxis().set_visible(False)


axis[0, 2].hist(hash3, bins=n_bins, edgecolor='black', color='yellow')
axis[0, 2].set_title("HASH 3")
axis[0, 2].get_xaxis().set_visible(False)
axis[0, 2].get_yaxis().set_visible(False)

axis[1, 0].hist(hash4, bins=n_bins, edgecolor='black', color='green')
axis[1, 0].set_title("HASH 4")
axis[1, 0].get_xaxis().set_visible(False)
axis[1, 0].get_yaxis().set_visible(False)

axis[1, 1].hist(hash5, bins=n_bins, edgecolor='black', color='blue')
axis[1, 1].set_title("HASH 5")
axis[1, 1].get_xaxis().set_visible(False)
axis[1, 1].get_yaxis().set_visible(False)

axis[1, 2].hist(hash6, bins=n_bins, edgecolor='black', color='purple')
axis[1, 2].set_title("HASH 6")
axis[1, 2].get_xaxis().set_visible(False)
axis[1, 2].get_yaxis().set_visible(False)

plt.tight_layout()

plt.show()
