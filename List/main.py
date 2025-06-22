import time
from ctypes import CDLL, POINTER, c_int, c_void_p, c_int64

intList = CDLL("./List/intList.dll")
# 加载动态链接库

# 创建链表
intList.createIntList.restype = c_void_p

# 添加节点
intList.addIntNode.argtypes = [c_void_p, c_int64]
intList.addIntNode.restype = c_int

# 释放链表
intList.freeIntList.argtypes = [c_void_p]
intList.freeIntList.restype = None
# 插入节点
intList.insertIntNode.argtypes = [c_void_p, c_int, c_int64]
intList.insertIntNode.restype = c_int
# 删除节点
intList.deleteIntNode.argtypes = [c_void_p, c_int]
intList.deleteIntNode.restype = c_int

# 新增：获取链表长度和内容
intList.getIntListLength.argtypes = [c_void_p]
intList.getIntListLength.restype = c_int
intList.copyIntListToArray.argtypes = [c_void_p, POINTER(c_int64), c_int]
intList.copyIntListToArray.restype = c_int
intList.getIntNodeValue.argtypes = [c_void_p, c_int, POINTER(c_int64)]
intList.getIntNodeValue.restype = c_int
#修改链表内容
intList.modifyIntNode.argtypes = [c_void_p, c_int, c_int64]
intList.modifyIntNode.restype = c_int

def get_list_content(head):
    length = intList.getIntListLength(head)
    arr_type = c_int64 * length
    arr = arr_type()
    intList.copyIntListToArray(head, arr, length)
    return list(arr)

def get_node_value(head, position):
    value = c_int64()
    res = intList.getIntNodeValue(head, position, value)
    if res == 0:
        return value.value
    else:
        raise IndexError("位置超出范围")

# 示例用法
# head = intList.createIntList()
# intList.addIntNode(head, 123)
# intList.addIntNode(head, 456)
# intList.addIntNode(head, 789)
# content = get_list_content(head)
# print("链表内容：", content)
# intList.freeIntList(head)

#测试样例
def test():
    time1= time.time()
    print("开始测试...")
    head = intList.createIntList()
    assert intList.addIntNode(head, 123) == 0
    assert intList.addIntNode(head, 456) == 0
    assert intList.addIntNode(head, 789) == 0
    print(get_list_content(head))
    print(intList.insertIntNode(head, 222, 3))
    assert intList.insertIntNode(head, 431, 2) == 0
    print("插入节点后：")
    print(get_list_content(head))
    assert intList.deleteIntNode(head, 1) == 0
    print("删除节点后：")
    print(get_list_content(head))
    print("获取节点值：")
    try:
        print(get_node_value(head, 2))  # 获取位置2的节点值
    except IndexError as e:
        print(e)
    try:
        print(get_node_value(head, 5))  # 尝试获取超出范围的节点值
    except IndexError as e:
        print(e)
    intList.modifyIntNode(head, 22, 3)
    print("修改节点值后：")
    print(get_list_content(head))
    print("链表长度：", intList.getIntListLength(head))
    intList.freeIntList(head)
    print("All tests passed.")
    time2 = time.time()
    print("测试完成，耗时：", time2 - time1, "秒")

if __name__ == "__main__":
    
    test()
   
    # 运行测试
    # test()  # Uncomment to run tests