import re
import sys

f_input = open('calc.in')
f_output = open('calc.out', 'w')
lines = []
digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
t_digits = ['sifir', 'bir', 'iki', 'uc', 'dort', 'bes', 'alti', 'yedi', 'sekiz', 'dokuz']
values = ['dogru', 'yanlis']
a_ops = ['arti', 'eksi', 'carpi', '+', '-', '*']
l_ops = ['ve', 'veya']
par_ac = ['(', 'ac-parantez']
par_kapa = [')', 'kapa-parantez']
a_var = []
l_var = []
init_statements = {}
mid_statements = {}
title2 = False
title3 = False


def syn_error():
    f_output.write('Dont Let Me Down')
    f_input.close()
    f_output.close()
    sys.exit()


for line in f_input:
    if not re.search('^ *$', line):
        lines.append(line)
if not re.search('^ *AnaDegiskenler *$', lines[0]):
    syn_error()
for line in lines[1:]:
    if title3:
        if re.search('^ *Sonuc *$', line):
            syn_error()
    if title2:
        if re.search('^ *YeniDegiskenler *$', line):
            syn_error()
        if re.search('^ *Sonuc *$', line):
            title3 = True
            title3_index = lines.index(line)
    if re.search('^ *YeniDegiskenler *$', line):
        title2 = True
        title2_index = lines.index(line)
    if re.search('^ *AnaDegiskenler *$', line):
        syn_error()
if not (title2 and title3):
    syn_error()
init_statement = [a for a in lines[1:title2_index]]
mid_statement = [b for b in lines[title2_index + 1:title3_index]]
sonuc = [c for c in lines[title3_index+1:]]
if len(sonuc) > 1:
    syn_error()
for line in init_statement:
    if not re.search('^ *[A-Za-z0-9]+ +degeri +[0-9a-z. ]+ +olsun *$', line):
        syn_error()
for line in mid_statement:
    if not re.search('^ *[A-Za-z0-9]+ +degeri +[0-9a-zA-Z(). *+-]+ +olsun *$', line):
        syn_error()
for line in init_statement:
    var = str(re.findall('^ *([A-Za-z0-9]+) +degeri', line)[0])
    value = str(re.findall('degeri +([0-9a-z. ]*[0-9a-z.]+) +olsun', line)[0])
    if var in init_statements.keys():
        syn_error()
    else:
        init_statements[var] = value
for key, value in init_statements.items():
    if len(key) > 10:
        syn_error()
    if (key in (digits + t_digits + values + a_ops + l_ops)) or key == 'Sonuc':
        syn_error()
    if (value in digits) or (value in t_digits):
        a_var.append(key)
    elif re.search(r'^[0-9]\.[0-9]$', value):
        a_var.append(key)
    elif re.search('^([a-z]+) +nokta +([a-z]+)$', value):
        temp_digits = re.findall('^([a-z]+) +nokta +([a-z]+)$', value)
        for digit_tuple in temp_digits:
            for digit in digit_tuple:
                if not (digit in t_digits):
                    syn_error()
        a_var.append(key)
    elif value in values:
        l_var.append(key)
    else:
        syn_error()
for line in mid_statement:
    var = str(re.findall('^ *([A-Za-z0-9]+) +degeri', line)[0])
    value = str(re.findall('degeri +([0-9A-Za-z(). *+-]*[0-9A-Za-z().*+-]+) +olsun', line)[0])
    if var in mid_statements.keys():
        syn_error()
    elif var in init_statements.keys():
        syn_error()
    else:
        mid_statements[var] = value
for key, value in mid_statements.items():
    if len(key) > 10:
        syn_error()
    if (key in (digits + t_digits + values + a_ops + l_ops)) or key == 'Sonuc':
        syn_error()
    temp_value = value.split()
    a_var_value = False
    l_var_value = False
    par_count = 0
    a_ops_count = 0
    a_term_count = 0
    l_ops_count = 0
    l_term_count = 0
    for index in range(len(temp_value)):
        if (temp_value[index] in (digits + t_digits + a_var + a_ops)) or re.search(r'^[0-9]\.[0-9]$', temp_value[index]):
            if temp_value[index] in a_ops:
                a_ops_count += 1
                if index == 0 or index == len(temp_value) - 1:
                    syn_error()
                elif (temp_value[index - 1] in a_ops) or (temp_value[index + 1] in a_ops):
                    syn_error()
            else:
                a_term_count += 1
            a_var_value = True
        elif temp_value[index] == 'nokta':
            if index == 0 or index == len(temp_value) - 1:
                syn_error()
            elif (temp_value[index - 1] not in t_digits) or (temp_value[index + 1] not in t_digits):
                syn_error()
            a_term_count -= 1
        elif temp_value[index] in (values + l_ops + l_var):
            if temp_value[index] in l_ops:
                l_ops_count += 1
                if index == 0 or index == len(temp_value) - 1:
                    syn_error()
                elif (temp_value[index - 1] in l_ops) or (temp_value[index + 1] in l_ops):
                    syn_error()
            else:
                l_term_count += 1
            l_var_value = True
        elif temp_value[index] in par_ac:
            if index < len(temp_value) - 1 and (temp_value[index + 1] in (par_kapa + a_ops + l_ops)):
                syn_error()
            if index > 0 and (temp_value[index - 1] not in (l_ops + a_ops + par_ac)):
                syn_error()
            par_count += 1
        elif temp_value[index] in par_kapa:
            if par_count == 0:
                syn_error()
            if index < len(temp_value) - 1 and (temp_value[index + 1] not in (a_ops + l_ops + par_kapa)):
                syn_error()
            if temp_value[index - 1] in a_ops + l_ops:
                syn_error()
            par_count -= 1
        else:
            syn_error()
    if par_count != 0:
        syn_error()
    if a_ops_count != a_term_count - 1:
        if a_var_value:
            syn_error()
    if l_ops_count != l_term_count - 1:
        if l_var_value:
            syn_error()
    if a_var_value == l_var_value:
        syn_error()
    if a_var_value:
        a_var.append(key)
    elif l_var_value:
        l_var.append(key)
if len(sonuc) == 1:
    if not re.search('^ *[0-9A-Za-z(). *+-]*[0-9A-Za-z().*+-]+ *$', sonuc[0]):
        syn_error()
    temp_sonuc = sonuc[0].split()
    a_sonuc_value = False
    l_sonuc_value = False
    par_count = 0
    a_ops_count = 0
    a_term_count = 0
    l_ops_count = 0
    l_term_count = 0
    for index in range(len(temp_sonuc)):
        if (temp_sonuc[index] in digits + t_digits + a_var + a_ops) or re.search(r'^[0-9]\.[0-9]$', temp_sonuc[index]):
            if temp_sonuc[index] in a_ops:
                a_ops_count += 1
                if index == 0 or index == len(temp_sonuc) - 1:
                    syn_error()
                elif (temp_sonuc[index - 1] in a_ops) or (temp_sonuc[index + 1] in a_ops):
                    syn_error()
            else:
                a_term_count += 1
            a_sonuc_value = True
        elif temp_sonuc[index] == 'nokta':
            if index == 0 or index == len(temp_sonuc) - 1:
                syn_error()
            elif (temp_sonuc[index - 1] not in t_digits) or (temp_sonuc[index + 1] not in t_digits):
                syn_error()
            a_term_count -= 1
        elif temp_sonuc[index] in values + l_ops + l_var:
            if temp_sonuc[index] in l_ops:
                l_ops_count += 1
                if index == 0 or index == len(temp_sonuc) - 1:
                    syn_error()
                elif (temp_sonuc[index - 1] in l_ops) or (temp_sonuc[index + 1] in l_ops):
                    syn_error()
            else:
                l_term_count += 1
            l_sonuc_value = True
        elif temp_sonuc[index] in par_ac:
            if temp_sonuc[index + 1] in (par_kapa + a_ops + l_ops):
                syn_error()
            if index > 0 and (temp_sonuc[index - 1] not in (l_ops + a_ops + par_ac)):
                syn_error()
            par_count += 1
        elif temp_sonuc[index] in par_kapa:
            if par_count == 0:
                syn_error()
            if index < len(temp_sonuc) - 1 and (temp_sonuc[index + 1] not in (a_ops + l_ops + par_kapa)):
                syn_error()
            if temp_sonuc[index - 1] in (a_ops + l_ops):
                syn_error()
            par_count -= 1
        else:
            syn_error()
    if par_count != 0:
        syn_error()
    if a_ops_count != a_term_count - 1:
        if a_sonuc_value:
            syn_error()
    if l_ops_count != l_term_count - 1:
        if l_sonuc_value:
            syn_error()
    if a_sonuc_value == l_sonuc_value:
        syn_error()

f_output.write('Here Comes the Sun')
f_input.close()
f_output.close()
