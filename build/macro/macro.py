particleNum = 500000#总粒子数
# exceptNum = 300000
i = 10

#以读取方式打开需要修改的文件为f
f = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/run0808/HPGeEfficency/build/macro/runuser2.mac', 'r', encoding='utf-8')

#将文件中的内容写入数组new[]
new=[]
for line in f:
    new.append(line)
f.close()

while i <= 10000:#循环过程

    #在数组new[]中修改需要改变的参数
    new[8]='/gun/energy {} keV\n'.format(i)
    new[10]='/run/beamOn {}\n'.format(particleNum)
    # new[84]='  if (fEdep == particleEnergy)\n'

    #以覆盖写的方式打开需要修改的文件
    f = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/run0808/HPGeEfficency/build/macro/runuser{}.mac'.format(i), 'w', encoding='utf-8')

    #将数组new[]中的内容覆盖写到文件中
    for n in new:
        f.write(n)
    f.close()

    i += 1