function block_out = update_app_designer(block,~)

persistent theta_o_plot
persistent theta_o_dot_plot
persistent theta_1_plot
persistent theta_1_dot_plot
persistent ctrl_action_plot

theta_o = get_param('LQR_MODEL/Out_1', 'RuntimeObject');
theta_o_dot = get_param('LQR_MODEL/Out_2', 'RuntimeObject');
theta_1 = get_param('LQR_MODEL/Out_3', 'RuntimeObject');
theta_1_dot = get_param('LQR_MODEL/Out_4', 'RuntimeObject');
control_action = get_param('LQR_MODEL/Out_5', 'RuntimeObject');

% convert them to string:

theta_o_dot_guage = num2str(theta_o_dot.InputPort(1).Data);
theta_1_dot_guage = num2str(theta_1_dot.InputPort(1).Data);

% Check for all tags in GUI:
all_tag_objects = findall(0, '-property', 'tag');
all_tags = get(all_tag_objects, 'tag');

[tf, idx] = ismember('Out_1', all_tags);
if tf
    theta_o_plot = all_tag_objects(idx);
end

[tf, idx] = ismember('Out_2', all_tags);
if tf
    theta_o_dot_plot = all_tag_objects(idx);
    st1 = all_tag_objects(idx);
end

[tf, idx] = ismember('Out_3', all_tags);
if tf
    theta_1_plot = all_tag_objects(idx);
end

[tf, idx] = ismember('Out_4', all_tags);
if tf
    theta_1_dot_plot = all_tag_objects(idx);
end

[tf, idx] = ismember('Out_5', all_tags);
if tf
    ctrl_action_plot = all_tag_objects(idx);
end

[tf, idx] = ismember('Out_6', all_tags);
if tf
    st1 = all_tag_objects(idx);
end

[tf, idx] = ismember('Out_7', all_tags);
if tf
    st2 = all_tag_objects(idx);
end

XData = get_param('LQR_MODEL', 'SimulationTime');

% Set Guage Speeds:
set(st1, 'Value', abs(str2double(theta_o_dot_guage)));
set(st2, 'Value', abs(str2double(theta_1_dot_guage)));
% Plot data of theta_o on its plot:
theta_o_Data = theta_o.InputPort(1).Data;
plot(theta_o_plot, XData, theta_o_Data, '-o','LineWidth',3,'MarkerSize',1);
hold(theta_o_plot, 'on');

% Plot data of theta_o_dot on its plot:
theta_o_dot_Data = theta_o_dot.InputPort(1).Data;
plot(theta_o_dot_plot, XData, theta_o_dot_Data, '-o','LineWidth',3,'MarkerSize',1);
hold(theta_o_dot_plot, 'on');

% Plot data of theta_1 on its plot:
theta_1_Data = theta_1.InputPort(1).Data;
plot(theta_1_plot, XData, theta_1_Data, '-o','LineWidth',3,'MarkerSize',1);
hold(theta_1_plot, 'on');

% Plot data of theta_1_dot on its plot:
theta_1_dot_Data = theta_1_dot.InputPort(1).Data;
plot(theta_1_dot_plot, XData, theta_1_dot_Data, '-o','LineWidth',3,'MarkerSize',1);
hold(theta_1_dot_plot, 'on');

% Plot data of control action on its plot:
ctrl_action_Data = control_action.InputPort(1).Data;
plot(ctrl_action_plot, XData, ctrl_action_Data, '-o','LineWidth',3,'MarkerSize',1);
hold(ctrl_action_plot, 'on');