x = int(input())
y = int(input())
g = int(input())

# DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE
board_length = x + g + 1
position = int((y - 1) / 2)
line_dict = {}
distance_dict = {}
size = x * y
move_count = -1
score = 0
exit_val = False
crash = False
for line in range(1, board_length + 2):
    if line <= x:
        line_lst = []
        for v in range(y):
            line_lst.append('*')
        line_dict[line] = line_lst
    elif line <= x + g:
        line_lst = []
        for s in range(y):
            line_lst.append(' ')
        line_dict[line] = line_lst
    elif line == board_length:
        line_dict[line] = []
        for p in range(y):
            if p == position:
                line_dict[line].append('@')
            else:
                line_dict[line].append(' ')
    else:
        line_dict[line] = 72 * '-'
for column in range(y):
    distance_dict[column] = g
while size > 0:
    if move_count > -1:
        print('Choose your action!')
        move = input()
        move = move.lower()
        if move == 'fire':
            for line in line_dict.values():
                if line[position] == '*':
                    score += 1
                    size -= 1
                    break
            for line in range(distance_dict[position] + 1):
                if line == distance_dict[position]:
                    if line == 0:
                        line_dict[board_length - 1][position] = ' '
                    elif line == board_length - 1:
                        line_dict[board_length - line][position] = ' '
                    else:
                        line_dict[board_length - line - 1][position] = ' '
                        line_dict[board_length - line][position] = ' '
                elif line == 0:
                    line_dict[board_length - line - 1][position] = '|'
                    for line2 in range(1, board_length + 2):
                        line_str = ''
                        for e in line_dict[line2]:
                            line_str += e
                        print(line_str)
                elif line < distance_dict[position]:
                    line_dict[board_length - line - 1][position] = '|'
                    line_dict[board_length - line][position] = ' '
                    for line2 in range(1, board_length + 2):
                        line_str = ''
                        for e in line_dict[line2]:
                            line_str += e
                        print(line_str)
            star = False
            for n in range(board_length - 1, 0, -1):
                if line_dict[n][position] == '*':
                    star = True
                    distance_dict[position] = board_length - 1 - n
                    break
            if not star:
                distance_dict[position] = board_length - 1
            if size == 0:
                break
        if move == 'left' and position >= 1:
            position = position - 1
            position_lst = []
            for p in range(y):
                if p == position:
                    position_lst.append('@')
                else:
                    position_lst.append(' ')
            line_dict[board_length] = position_lst
        elif move == 'right' and position < y - 1:
            position = position + 1
            position_lst = []
            for p in range(y):
                if p == position:
                    position_lst.append('@')
                else:
                    position_lst.append(' ')
            line_dict[board_length] = position_lst
        elif move == 'exit':
            exit_val = True
            break
    move_count += 1
    if move_count > 0 and move_count % 5 == 0:
        if g != 0:
            g = g - 1
        for column in range(y):
            if line_dict[board_length - 1][column] == '*':
                crash = True
                break
        if crash:
            break
        for d in range(board_length - 1 - g, 0, -1):
            if d <= board_length - g - x - 1:
                line_lst = []
                for s in range(y):
                    line_lst.append(' ')
                line_dict[d] = line_lst
            else:
                line_dict[d] = line_dict[d - 1]
        for m in range(y):
            star = False
            for n in range(board_length - 1, 0, -1):
                if line_dict[n][m] == '*':
                    distance_dict[m] = board_length - 1 - n
                    star = True
                    break
            if not star:
                distance_dict[m] = board_length - 1
    for line in range(1, board_length + 2):
        line_str = ''
        for e in line_dict[line]:
            line_str += e
        print(line_str)
if exit_val:
    for line in range(1, board_length + 2):
        line_str = ''
        for e in line_dict[line]:
            line_str += e
        print(line_str)
    print('YOUR SCORE:', score)
if crash:
    print('GAME OVER')
    for line in range(1, board_length + 2):
        line_str = ''
        for e in line_dict[line]:
            line_str += e
        print(line_str)
    print('YOUR SCORE:', score)
if size == 0:
    print('YOU WON!')
    for line in range(1, board_length + 2):
        line_str = ''
        for e in line_dict[line]:
            line_str += e
        print(line_str)
    print('YOUR SCORE:', score)
# DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE
