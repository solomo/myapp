import sys,os

"""
初始化类名
"""
def create_class(table):
    return "<?php\nClass %s"%(table.capitalize())

"""
初始类中的函数
"""
def create_get_set_func(field):
    return "\n\tpublic function set%s($%s){\n\t\t$this->%s = $%s;\n\t}\n\n\tpublic function get%s(){\n\t\treturn $this->%s;\n\t}\n"%(field.capitalize(),field, field, field,field.capitalize(),field)

"""
初始化构造函数
"""
def create_construct_func(construct_argv, construct_line):
    return "\tpublic function __construct(%s){\t%s\n\t}"%(construct_argv, construct_line)

"""
初始化成员变量
"""
def create_member(field):
    return "\tprivate $%s;\n"%(field)
