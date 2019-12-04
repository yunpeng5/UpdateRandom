from scipy.stats import chisquare

Sname=0
Sobserve=1
Sexpect=2
f=open('chi_square_test','r')
line=f.readline()
stage=0
count=0
while line:
    if stage==Sname:
        print(line.replace('\n',''))
    elif stage==Sobserve:
        line=[float(i) for i in line.replace('\n','').split()]
        observe_value=line
    else:
        line=[float(i) for i in line.replace('\n','').split()]
        expect_value=line
        count+=1
        print(len(observe_value)-1)
        print(chisquare(observe_value,expect_value))
        print()
    line=f.readline()
    stage=(stage+1)%3
f.close()