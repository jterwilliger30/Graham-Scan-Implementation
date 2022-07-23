import matplotlib.pyplot as plt

# Opens file, appends lines in file with \n stripped off into a list
with open("./output.csv", "r", encoding="utf-8") as infile:
    lst = []
    for i in infile:
        lst.append(i.strip())

# Deletes "All Points:" line
del lst[0]


for i in range(len(lst)):
    if lst[i] == "Hull Points:":
        pass
    # Strips parentheses off the values
    else:
        lst[i] = lst[i].strip("()")

    # Splits x and y value into two values in a sub-list
    lst[i] = lst[i].split(", ")

    # Casts numbers from string to integers
    if lst[i][0].isdecimal():
        lst[i][0] = int(lst[i][0])
        lst[i][1] = int(lst[i][1])

# Lists containing all points
xAll = []
yAll = []

# Lists containing hull points which will be plotted using line segments
xHull = []
yHull = []

for i in range(len(lst)):

    # Appends all Hull Points
    if lst[i][0] == "Hull Points:":
        # Passes to the first point value after "Hull Points:"
        i+=1

        # Continues until the second to last list item
        while lst[i] != lst[len(lst) - 1]:
            # Appends x and y value
            xHull.append(lst[i][0])
            yHull.append(lst[i][1])

            # Continues to next list item
            i+=1

        # Appends the last list item x and y value
        xHull.append(lst[i][0])
        yHull.append(lst[i][1])

        # Exits the for loop
        break

    # Ignores empty string
    elif lst[i][0] == "":
            continue

    # Appends all points, stopping at "Hull Points:"
    else:
        xAll.append(lst[i][0])
        yAll.append(lst[i][1])

# Plots all points in a scatterplot
plt.scatter(xAll, yAll)

# Appends P0 to the end so that lines start and end on the same point
xHull.append(xHull[0])
yHull.append(yHull[0])

# Plots line segments
for i in range(len(xHull)):
    plt.plot(xHull, yHull, "r", linestyle="-")

# Saves .png of the scatterplot
plt.savefig("scatterplot")