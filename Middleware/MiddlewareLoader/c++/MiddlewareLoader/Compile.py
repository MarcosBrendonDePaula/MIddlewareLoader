import os
# Fuctions
def getAll(path="",exp=".cpp"):
    files = []
    for diretorio, subpastas, arquivos in os.walk(path):
        for arquivo in arquivos:
            arq_path = os.path.join(diretorio, arquivo)
            if(arq_path.find(exp) >=0):
                files.append(arq_path.replace("\\","/"))
    return files

def ListToStr(list = []):
    string = ""
    for i in list:
        string+=i+" "
    return string


# CONFIGS
Compiller = "g++"
output = ""
include_path   = "include"
src_path       = "src"


flags = [
    "-std=c++17"
]


link_libraries = [
    "ws2_32"
]

cpp_files = getAll(include_path,".cpp")
cpp_src_Server = getAll(src_path+"/Server",".cpp")
cpp_src_Client = getAll(src_path+"/Client",".cpp")

print("Compilando Servidor")
os.system("{comp} {flags} {includes} {src} -o Server -l {libraries} -I {include_path}".format(
    comp = Compiller,
    flags = ListToStr(flags),  
    includes = ListToStr(cpp_files),
    src = ListToStr(cpp_src_Server),
    out = output,
    libraries = ListToStr(link_libraries),
    include_path = include_path
))

print("Compilando Client")
os.system("{comp} {flags} {includes} {src} -o Client -l {libraries} -I {include_path}".format(
    comp = Compiller,  
    flags = ListToStr(flags),
    includes = ListToStr(cpp_files),
    src = ListToStr(cpp_src_Client),
    out = output,
    libraries = ListToStr(link_libraries),
    include_path = include_path
))