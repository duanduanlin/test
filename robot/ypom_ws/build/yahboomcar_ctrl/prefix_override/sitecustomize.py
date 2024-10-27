import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/work/test/robot/ypom_ws/install/yahboomcar_ctrl'
