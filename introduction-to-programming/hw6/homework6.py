f_input = open('crime_scene.txt')
f_part_1 = open('solution_part1.txt', 'w')
f_part_2 = open('solution_part2.txt', 'w')
f_part_3 = open('solution_part3.txt', 'w')
input_str = f_input.read()
input_lst = input_str.split()
weight_limit = int(input_lst[0])
time_limit = int(input_lst[1])
evidence_dict = {}
possible_outcomes = []
higher = []
lower = []


def read_input(lst):
    if len(lst) == 0:
        return
    evidence_dict[int(lst[0])] = [int(lst[1]), int(lst[2]), int(lst[3])]
    read_input(lst[4:])


def gather_evidence(gathered_lst, free_lst):
    if len(gathered_lst) > 0:
        copy = gathered_lst.copy()
        if copy not in possible_outcomes:
            possible_outcomes.append(copy)
    if len(free_lst) == 0:
        return
    gathered_lst.append(free_lst[0])
    gather_evidence(gathered_lst, free_lst[1:])
    gathered_lst.pop()
    gather_evidence(gathered_lst, free_lst[1:])


def find_value(lst):
    if len(lst) == 0:
        return 0
    return evidence_dict[lst[0]][2] + find_value(lst[1:])


def higher_lower_value(lst, integer):
    if len(lst) == 0:
        return
    global higher
    global lower
    if find_value(lst[0]) <= integer:
        lower.append(lst[0])
    elif find_value(lst[0]) > integer:
        higher.append(lst[0])
    higher_lower_value(lst[1:], integer)


def higher_lower(lst, integer):
    if len(lst) == 0:
        return
    global higher
    global lower
    if lst[0] <= integer:
        lower.append(lst[0])
    elif lst[0] > integer:
        higher.append(lst[0])
    higher_lower(lst[1:], integer)


def quick_sort(lst):
    if len(lst) <= 1:
        return lst
    global higher
    global lower
    lower = []
    higher = []
    if type(lst[0]) == list:
        higher_lower_value(lst[1:], find_value(lst[0]))
    else:
        higher_lower(lst[1:], lst[0])
    higher_copy = higher.copy()
    lower_copy = lower.copy()
    return quick_sort(lower_copy) + [lst[0]] + quick_sort(higher_copy)


read_input(input_lst[3:])
gather_evidence([], list(evidence_dict.keys()))
rearranged_evidence = quick_sort(possible_outcomes)


def find_weight(lst):
    if len(lst) == 0:
        return 0
    return evidence_dict[lst[0]][0] + find_weight(lst[1:])


def find_time(lst):
    if len(lst) == 0:
        return 0
    return evidence_dict[lst[0]][1] + find_time(lst[1:])


def check_weight(lst, integer):
    if len(lst) == 0:
        return []
    if find_weight(lst[-1]) <= integer:
        return lst[-1]
    return check_weight(lst[:-1], integer)


def check_time(lst, integer):
    if len(lst) == 0:
        return []
    if find_time(lst[-1]) <= integer:
        return lst[-1]
    return check_time(lst[:-1], integer)


def check_both(lst, time, weight):
    if len(lst) == 0:
        return []
    if find_time(lst[-1]) <= time:
        if find_weight(lst[-1]) <= weight:
            return lst[-1]
    return check_both(lst[:-1], time, weight)


def lst_2_str(lst, string):
    if len(lst) == 0:
        return string
    string += str(lst[0]) + ' '
    return lst_2_str(lst[1:], string)


f_input.close()
solution_1 = check_weight(rearranged_evidence, weight_limit)
f_part_1.write(str(find_value(solution_1)) + '\n' + lst_2_str(quick_sort(solution_1), ''))
f_part_1.close()
solution_2 = check_time(rearranged_evidence, time_limit)
f_part_2.write(str(find_value(solution_2)) + '\n' + lst_2_str(quick_sort(solution_2), ''))
f_part_2.close()
solution_3 = check_both(rearranged_evidence, time_limit, weight_limit)
f_part_3.write(str(find_value(solution_3)) + '\n' + lst_2_str(quick_sort(solution_3), ''))
f_part_3.close()
