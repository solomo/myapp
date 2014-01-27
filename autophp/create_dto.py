import pymysql
import sys,os
import configparser
import codecs
sys.path.append(sys.path[0]+'/util') 
import util

#不需要生成代码的字段
CONST_FIELD_STR = {'id'}

def create():
    cfgfile="conf/config.ini"
    config = configparser.ConfigParser()
    config.readfp(codecs.open(cfgfile, "r", "utf-8-sig"))
    db_host = config.get("db","db_host")
    db_port = int(config.get("db","db_port"))
    db_user = config.get("db","db_user")
    db_pass = config.get("db","db_pass")
    
    #获取数据库名
    db_name = sys.argv[1]
    #获取表名
    table = sys.argv[2]
    #数据库连接
    conn = pymysql.connect(host=db_host, port=db_port, user=db_user, passwd=db_pass, db=db_name)
    cur = conn.cursor()
    #查询表结构
    cur.execute("desc "+table)
    flag=True
    construct_argv = "";
    construct_line = "";
    function_line = "";
    member_line = "";
    #遍历
    for row in cur:
        field = row[0]
        #剔除掉不需要生成代码的字段
        if field in CONST_FIELD_STR:
            continue
        member_line += util.create_member(field)
        if flag:
            construct_argv += "$%s"%(field)
            flag = False
        else:
            construct_argv += ", $%s"%(field)
        construct_line += "\n\t\t$this->%s = $%s;"%(field, field)
        function_line += util.create_get_set_func(field);
    
    #组装成class代码
    print(util.create_class(table)+"{")
    print(member_line)
    print(util.create_construct_func(construct_argv, construct_line))
    print(function_line)
    print("}")
    cur.close()
    conn.close()
#入口处理
if __name__ == '__main__' :
    create()
