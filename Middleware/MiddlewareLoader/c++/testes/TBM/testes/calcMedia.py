pos = 0
ms = 0

for x in range(0, 8):
    valores = []
    for i in range(0, 2):
        f = open(str(pos+i)+".csv", "r")
        lines = f.readlines()
        lines.pop(0)
        for l in lines:
            if(float(l.split(";\n")[0].split(",")[0]) < 5):
                valores.append(float(l.split(";\n")[0].split(",")[0]))
                ms = float(l.split(";\n")[0].split(",")[1])
    sum=0
    for v in valores:
        sum += v
        pass
    print(sum/len(valores), ms)
    pos += 2
