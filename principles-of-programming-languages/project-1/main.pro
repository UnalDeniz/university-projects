% deniz ünal
% 2019400234
% compiling: yes
% complete: yes
:- ['cmpecraft.pro'].

:- init_from_map.

% 10 points
% manhattan_distance(+A, +B, -Distance) :- .

manhattan_distance([], [], 0). %base condition
%takes the head of the lists and add their difference to the sum.
manhattan_distance([H1|T1], [H2|T2], R1) :- H1 > H2, !, manhattan_distance(T1, T2, R2), R1 is R2 + H1 - H2.
manhattan_distance([H1|T1], [H2|T2], R1) :- H1 < H2, !, manhattan_distance(T1, T2, R2), R1 is R2 + H2 - H1.
manhattan_distance([H1|T1], [H1|T2], R1) :- manhattan_distance(T1, T2, R1).

% 10 points
% minimum_of_list(+List, -Minimum) :- .

minimum_of_list([H|T], H) :- length(T, 0), !. %if there is only one element in the list it is the smallest element (base condition).
%if the head is smaller than minimum of the body of the list, head is the minimum of the whole list.
minimum_of_list([H|T], R) :- minimum_of_list(T, R), H > R, !.
minimum_of_list([H|T], H) :- minimum_of_list(T, R), H < R.

% 10 points
% find_nearest_type(+State, +ObjectType, -ObjKey, -Object, -Distance) :- .

%given X and Y calculates the distance from the current position in the State.
how_far(State, X, Y, Distance) :- State = [A|_], get_dict(x, A, CurrentX), get_dict(y, A, CurrentY), manhattan_distance([X, Y], [CurrentX, CurrentY], Distance).

%first finds an element that is from the given type and using it as an argument finds the smallest distance, then finds the elements that are that far from the location in the state.
find_nearest_type(State, ObjectType, ObjKey, Object, Distance) :- find_one_distance(State, ObjectType, TempDistance),
                                find_smallest_distance(State, ObjectType, TempDistance, Distance), !, State = [_,O|_], get_dict(ObjKey, O, Object),
                                get_dict(type, Object, ObjectType), get_dict(x, Object, ObjX),
                                get_dict(y, Object, ObjY), how_far(State, ObjX, ObjY, Distance).

%if there is only one object from the given type find_smallest_distance returns false, then the temporary distance is the distance of the only object.
find_nearest_type(State, ObjectType, ObjKey, Object, Distance) :- find_one_distance(State, ObjectType, Distance), State = [_,O|_],
                                get_dict(ObjKey, O, Object), get_dict(type, Object, ObjectType),  get_dict(x, Object, ObjX),
                                get_dict(y, Object, ObjY), how_far(State, ObjX, ObjY, Distance), !.

%finds an arbitrary object from the given type.
find_one_distance(State, ObjectType, Distance) :- State = [_,O|_], get_dict(_, O, Object), get_dict(type, Object, ObjectType),
                                                        get_dict(x, Object, ObjX), get_dict(y, Object, ObjY), how_far(State, ObjX, ObjY, Distance).

%given a distance as an argument, finds an object with a smaller distance, repeats this until there is no object with a smaller distance, annd returns that as the smallest distance.
find_smallest_distance(State, ObjectType, Distance, LastDistance) :- State = [_,O|_], get_dict(_, O, Object), get_dict(type, Object, ObjectType),
                                                                     get_dict(x, Object, ObjX), get_dict(y, Object, ObjY),
                                                                     how_far(State, ObjX, ObjY, RealDistance), RealDistance < Distance,
                                                                     not(find_smallest_distance(State, ObjectType, RealDistance, _)), !, LastDistance = RealDistance.

find_smallest_distance(State, ObjectType, Distance, LastDistance) :- State = [_,O|_], get_dict(_, O, Object), get_dict(type, Object, ObjectType),
                                                                     get_dict(x, Object, ObjX), get_dict(y, Object, ObjY),
                                                                     how_far(State, ObjX, ObjY, RealDistance), RealDistance < Distance,
                                                                     find_smallest_distance(State, ObjectType, RealDistance, LastDistance).

% 10 points
% navigate_to(+State, +X, +Y, -ActionList, +DepthLimit) :- .

in_same_column(State, X) :- State = [A|_], get_dict(x, A, X). %checks if the current X coordinate and the given X are same.
in_same_row(State, Y) :- State = [A|_], get_dict(y, A, Y). %checks if the current Y coordinate and the given Y are same.

%gives the action that is  needed to go to desired X coordinate.
row_action(State, X, NextX, Action) :- State = [A|_], get_dict(x, A, StateX), StateX < X, Action = go_right, NextX is X - 1. 
row_action(State, X, NextX, Action) :- State = [A|_], get_dict(x, A, StateX), StateX > X, Action = go_left, NextX is X + 1. 

%gives the action that is needed to go to desired Y coordinate.
column_action(State, Y, NextY, Action) :- State = [A|_], get_dict(y, A, StateY), StateY < Y, Action = go_down, NextY is Y - 1. 
column_action(State, Y, NextY, Action) :- State = [A|_], get_dict(y, A, StateY), StateY > Y, Action = go_up, NextY is Y + 1. 

navigate_to(State, X, Y, [], _) :- in_same_row(State, Y), in_same_column(State, X), !. %if the destination is reached, stops (base condition).
navigate_to(_, _, _, _, 0) :- !, fail. %if there are no moves remaining and the destination hasn't been reached yet, returns false.
%executes row and column actions until the destination is reached.
navigate_to(State, X, Y, ActionList, DepthLimit) :- ActionList = [Action|NextActions], (column_action(State, Y, NextY, Action), NextX = X; row_action(State, X, NextX, Action), NextY = Y), !, RemainingDepth is DepthLimit - 1, navigate_to(State, NextX, NextY, NextActions, RemainingDepth).


% 10 points
% chop_nearest_tree(+State, -ActionList) :- .

%combines the given lists 
combine_lists([], List2, List2). 
combine_lists([H1|B1], List2, [H1|B2]) :- combine_lists(B1, List2, B2).

%click on the object until the number of clicks reaches its hp.
click(Object, Clicked, [left_click_c]) :- get_dict(hp, Object, Clicked).
click(Object, Clicked, ActionList) :- get_dict(hp, Object, ObjectHP), ActionList = [Action|NextActions], Clicked < ObjectHP, Action = left_click_c, NextClicked is Clicked + 1, click(Object, NextClicked, NextActions).

%given an object type, finds its closest member, navigates to it and clicks it until number of clicks reaches its hp.
collect_nearest_type(State, ObjectType, ActionList) :- find_nearest_type(State, ObjectType, _, Object, Distance), get_dict(x, Object, ObjectX), get_dict(y, Object, ObjectY), navigate_to(State, ObjectX, ObjectY, ActionList1, Distance), click(Object, 0, ActionList2), combine_lists(ActionList1, ActionList2, ActionList).

%calls collect_nearest_type with tree type.
chop_nearest_tree(State, ActionList) :- collect_nearest_type(State, tree, ActionList).

% 10 points
% mine_nearest_stone(+State, -ActionList) :- .

%calls collect_nearest_type with stone type.
mine_nearest_stone(State, ActionList) :- collect_nearest_type(State, stone, ActionList).

%calls collect_nearest_type with cobblestone type.
mine_nearest_cobblestone(State, ActionList) :- collect_nearest_type(State, cobblestone, ActionList).

% 10 points
% gather_nearest_food(+State, -ActionList) :- .

%calls collect_nearest_type with food type.
gather_nearest_food(State, ActionList) :- collect_nearest_type(State, food, ActionList).

% 10 points
% collect_requirements(+State, +ItemType, -ActionList) :- .

%if the type doesn't require any logs, returns empty action list.
collect_logs(_, ItemType, []) :- item_info(ItemType, Reqs, _), not(get_dict(log, Reqs, _)), !.
%if there is enough logs in the inventory, ends the action list.
collect_logs([A|_], ItemType, []) :- get_dict(inventory, A, Inv), (get_dict(log, Inv, Collected); Collected = 0), item_info(ItemType, Reqs, _), get_dict(log, Reqs, Required), Collected >= Required, !.
%if there is not enough logs in the inventory, continues collecting.
collect_logs(State, ItemType, ActionList) :-  chop_nearest_tree(State, ActionList1), execute_actions(State, ActionList1,NextState), collect_logs(NextState, ItemType, ActionList2), combine_lists(ActionList1, ActionList2, ActionList).

%if the type doesn't require any sticks, returns empty action list.
collect_stick(_, ItemType, []) :- item_info(ItemType, Reqs, _), not(get_dict(stick, Reqs, _)), !.
%if there is enough sticks in the inventory, ends the action list.
collect_stick([A|_], ItemType, []) :- get_dict(inventory, A, Inv), (get_dict(stick, Inv, Collected); Collected = 0), item_info(ItemType, Reqs, _), get_dict(stick, Reqs, Required), Collected >= Required, !.
%if there is not enough sticks in the inventory, continues collecting.
collect_stick(State, ItemType, ActionList) :- collect_logs(State, stick, TempActionList), combine_lists(TempActionList, [craft_stick], ActionList1), execute_actions(State, ActionList1, NextState), collect_stick(NextState, ItemType, ActionList2), combine_lists(ActionList1, ActionList2, ActionList).

%if the type doesn't require any sticks, returns empty action list.
collect_cobblestone(_, ItemType, []) :- item_info(ItemType, Reqs, _), not(get_dict(cobblestone, Reqs, _)), !.
%if there is enough sticks in the inventory, ends the action list.
collect_cobblestone([A|_], ItemType, []) :- get_dict(inventory, A, Inv), (get_dict(cobblestone, Inv, Collected); Collected = 0), item_info(ItemType, Reqs, _), get_dict(cobblestone, Reqs, Required), Collected >= Required, !.
%if there is not enough sticks in the inventory, continues collecting.
collect_cobblestone(State, ItemType, ActionList) :- (mine_nearest_stone(State, ActionList1); mine_nearest_cobblestone(State, ActionList1)), !, execute_actions(State, ActionList1,NextState), collect_cobblestone(NextState, ItemType, ActionList2), combine_lists(ActionList1, ActionList2, ActionList).

%calls collect_stick, collect_logs and collect_cobblestones and combines the resulting actionlists.
collect_requirements(State, ItemType, ActionList) :- collect_stick(State, ItemType, ActionList1), (ActionList1 = [], NextState1 = State; execute_actions(State, ActionList1, NextState1)), collect_logs(NextState1, ItemType, ActionList2), (ActionList2 = [], NextState2 = NextState1; execute_actions(NextState1, ActionList2, NextState2)), combine_lists(ActionList1, ActionList2, ActionList3), collect_cobblestone(NextState2, ItemType, ActionList4), combine_lists(ActionList3, ActionList4, ActionList).

% 5 points
% find_castle_location(+State, -XMin, -YMin, -XMax, -YMax) :- .

%checks if there is an object in the given coordinate.
my_tile_occupied(X, Y, State) :-
    State = [_, StateDict, _],
    get_dict(_, StateDict, Object),
    get_dict(x, Object, X),
    get_dict(y, Object, Y).

tile_not_occupied(X, Y, State) :- not(my_tile_occupied(X, Y, State)).

%calls the find_castle starting from the left upper corner of the map.
find_castle_location(State, XMin, YMin, XMax, YMax) :- find_castle(State, 1, 1, XMax, YMax), XMin is XMax - 2, YMin is YMax - 2.

%checks if there is enough space fr a castle in the given coordinate.
find_castle(State, XMin, YMin, XMax, YMax) :- width(W), height(H), WM is W - 3, HM is H - 3, XMin < WM, YMin < HM, XMax is XMin + 2, YMax is YMin + 2, XMid is XMin + 1, YMid is YMin + 1,
                        tile_not_occupied(XMin, YMin, State), tile_not_occupied(XMin, YMid, State), tile_not_occupied(XMin, YMax, State),
                        tile_not_occupied(XMid, YMin, State), tile_not_occupied(XMid, YMid, State), tile_not_occupied(XMid, YMax, State),
                        tile_not_occupied(XMax, YMin, State), tile_not_occupied(XMax, YMid, State), tile_not_occupied(XMax, YMax, State).

%if there is not enough space checks the position in the right until end of the row, then continues checking from start of the next row.
find_castle(State, XMin, YMin, XMax, YMax) :- width(W), height(H), WM is W - 3, HM is H - 3, XMin < WM, YMin < HM, XMid is XMin + 1, find_castle(State, XMid, YMin, XMax, YMax).
find_castle(State, XMin, YMin, XMax, YMax) :- width(W), height(H), WM is W - 3, HM is H - 3, XMin >= WM, YMin < HM, YMid is YMin + 1, find_castle(State, 1, YMid, XMax, YMax).

% 15 points
% make_castle(+State, -ActionList) :- .

%if there is enough cobblestones in the inventory, stops collecting cobblestones.
collect_castle(State, []) :- State = [A|_], get_dict(inventory, A, Inventory), (get_dict(cobblestone, Inventory, Collected); Collected = 0), Collected >= 9, !.
%if there is not enough cobblestones in the inventory, continues collecting cobblestones.
collect_castle(State, ActionList) :- (mine_nearest_stone(State, ActionList1); mine_nearest_cobblestone(State, ActionList1)), !, execute_actions(State, ActionList1, NextState), collect_castle(NextState, ActionList2), combine_lists(ActionList1, ActionList2, ActionList).

%collects cobblestones, then seaches for a location, navigates to there and finally builds the castle and combines the corresponding actionlists for these actions.
make_castle(State, ActionList) :- collect_castle(State, ActionList1), execute_actions(State, ActionList1, NewState), find_castle_location(NewState, XMin, YMin, _, _), X is XMin + 1, Y is YMin + 1, how_far(NewState, X, Y, Distance), navigate_to(NewState, X, Y, ActionList2, Distance), combine_lists(ActionList1, ActionList2, ActionList3), combine_lists(ActionList3, [place_nw, place_n, place_ne, place_w, place_c, place_e, place_sw, place_s, place_se], ActionList).
