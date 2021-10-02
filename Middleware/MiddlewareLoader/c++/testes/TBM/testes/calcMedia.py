valores = []
for i in range(0,39):
    f = open(str(i)+".csv","r")
    lines = f.readlines()
    lines.pop(0)
    
    for l in lines:
        valores.append(float(l.split(";\n")[0]))
        pass
    pass

sum = 0
for v in valores:
    sum+=v
    pass
print(sum/len(valores))