def CreateFunction(name="",Args = [("int","x")],return_ = "void"):
    Cppfunction = "static {0} {1}({2})"
    CppRfunction = "static {return_:} {name:}({args:},std::string alvo){}"

    arg_list = ""
    for arg in Args:
        arg_list += "{type:} {name:},".format(type = arg[0],name = arg[1])
    arg_list = arg_list[:-1]
    Cppfunction = Cppfunction.format(return_,name,arg_list)
    Cppfunction+= "{" \
                   "\n" \
                   "\n" \
                   "\n" \
                   "}"

    CsharpFunction = "public {0} {1}({args})"

    return [("c++",Cppfunction)]
f1 = CreateFunction("teste",
                [
                    ("int","valor"),
                    ("std::string","nome"),
                    ("float","idade")
                ],
               return_= "int")
print(f1)