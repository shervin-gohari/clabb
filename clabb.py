import openpyxl as excel
import matplotlib.pyplot as plt

wb = excel.load_workbook('clabb.xlsx')

sheet_1 = wb['Uppslagning - Input']
sheet_2 = wb['Uppslagningar - Input']

#djb2
x1_column = sheet_1['A']
y1_column = sheet_1['B']

x1_column_list = [x1_column[x].value for x in range(len(x1_column))]
y1_column_list = [y1_column[x].value for x in range(len(y1_column))]

#tillpro-and
x2_column = sheet_1['C']
y2_column = sheet_1['D']

x2_column_list = [x2_column[x].value for x in range(len(x2_column))]
y2_column_list = [y2_column[x].value for x in range(len(y2_column))]

#tillpromodulo
x3_column = sheet_1['E']
y3_column = sheet_1['F']

x3_column_list = [x3_column[x].value for x in range(len(x3_column))]
y3_column_list = [y3_column[x].value for x in range(len(y3_column))]

#naiv
x4_column = sheet_1['G']
y4_column = sheet_1['H']

x4_column_list = [x4_column[x].value for x in range(len(x4_column))]
y4_column_list = [y4_column[x].value for x in range(len(y4_column))]

#Plottning

fig, axs = plt.subplots(2, 2)
axs[0, 0].plot(x1_column_list, y1_column_list)
axs[0, 1].plot(x2_column_list, y2_column_list)
axs[1, 0].plot(x3_column_list, y3_column_list)
axs[1, 1].plot(x4_column_list, y4_column_list)
plt.show()

#plt.plot(x_column_list,y_column_list)
#plt.show()
