#include "espresso_based.h"

/** 
 * 这里采用 ncurses 库来实现 brew 函数，请记得修改CMakeLists.txt文件
 * ncurses库的使用: https://hackmd.io/@G36maid/B1IO0cyO3#reference
 * 这里的 brew 函数其实并不完整，因为如果客户添加额外的原料是不能正确处理的
 * 想要能够处理派生类中的side_items成员，可以定义一个虚函数，然后在派生类
 * 中实现，并在此函数中调用，这里就不给出示例代码了，自己试试。
 */
void EspressoBased::brew()
{
    initscr();  // 初始化窗口对象
    curs_set(0);    // 隐藏光标
    noecho();

    int rows, cols; // 屏幕大小
    int win_rows = 25; // 新窗口高
    int win_cols = 90; // 新窗口宽
    int start_y, start_x; // 新窗口左下角坐标

    getmaxyx(stdscr, rows, cols); // 获取屏幕大小并存储
    start_x = (cols - win_cols) / 2;
    start_y = (rows - win_rows) / 2;
    
    // 创建新窗口
    WINDOW *win = newwin(win_rows, win_cols, start_y, start_x);
    box(win, 0 , 0);

    // 创建进度框
    mvwaddch(win, 2, 1, ACS_ULCORNER); // 左上角
    mvwaddch(win, 2, win_cols - 2, ACS_URCORNER); //右上角
    mvwaddch(win, 4, 1, ACS_LLCORNER); // 左下角
    mvwaddch(win, 4, win_cols - 2, ACS_LRCORNER); // 右下角
    // 绘制进度框水平线
    for (int i = 2; i < win_cols - 2; ++i)
    {
        mvwaddch(win, 2, i, ACS_HLINE);
    }
    for (int i = 2; i < win_cols - 2; ++i)
    {
        mvwaddch(win, 4, i, ACS_HLINE);
    }
    // 绘制进度框垂直线
    mvwaddch(win, 3, 1, ACS_VLINE);
    mvwaddch(win, 3, win_cols - 2, ACS_VLINE);
    // 显示相关信息
    mvwprintw(win, 3, 3, "brewing: ");
    mvwprintw(win, 3, win_cols - 6, "/100");
    mvwaddch(win, 3, win_cols - 10, ACS_VLINE);
    
    // 显示制作咖啡过程
    // 绘制已经制作的东西: 上部框
    mvwaddch(win, 5, (win_cols - 14) / 2, ACS_ULCORNER); // 左上角
    mvwaddch(win, 5, (win_cols + 14) / 2, ACS_URCORNER); //右上角
    for (int i = (win_cols - 14) / 2 + 1; i < (win_cols + 14) / 2; ++i)
    {
        mvwaddch(win, 5, i, ACS_HLINE);
    }

    int raw_material_h = 0; // 存储原料高度， 1 unit 对应高度为 2
    for(const auto &ingredient: _ingredients)
    {
        raw_material_h += ingredient->get_units() * 2;
    }

    // 绘制已经制作的东西: 下部框
    mvwaddch(win, 6 + raw_material_h, (win_cols - 14) / 2, ACS_LLCORNER); // 左下角
    mvwaddch(win, 6 + raw_material_h, (win_cols + 14) / 2, ACS_LRCORNER); //右下角
    for(int i = (win_cols - 14) / 2 + 1; i < (win_cols + 14) / 2; ++i)
    {
        mvwaddch(win, 6 + raw_material_h, i, ACS_HLINE);
    }
    
    // 绘制已经制作的东西: 左右边框
    for(int i = 6; i < 6 + raw_material_h; i++)
    {
        mvwaddch(win, i, (win_cols - 14) / 2, ACS_VLINE);
        mvwaddch(win, i, (win_cols + 14) / 2, ACS_VLINE);
    }

    std::string schedule = "#################################";
    mvwprintw(win, 3, 12, "%s", schedule.c_str());
    int cur_material_h = _ingredients[0]->get_units() * 2;
    int ingredients_index = 1;
    mvwprintw(win, 6 + raw_material_h - cur_material_h, (win_cols - 14) / 2 + 1, "-------------");
    mvwprintw(win, 6 + raw_material_h - cur_material_h + 1, (win_cols - 14) / 2 + 1, _ingredients[0]->get_name().c_str());
    wrefresh(win);
    for(int process = 38; process <= 100; process += 2)
    {
        napms(200); // 暂停 200ms 用于动态显示制作过程

        // 更新进度框
        mvwprintw(win, 3, 12, "%s", schedule.c_str());
        mvwprintw(win, 3, win_cols - 9, "%d", process);

        if(process == 60 || process == 80 || process == 100)
        {
            if(ingredients_index < _ingredients.size())
            {
                cur_material_h += _ingredients[ingredients_index]->get_units() * 2;
                if(ingredients_index != _ingredients.size() - 1)
                {
                    mvwprintw(win, 6 + raw_material_h - cur_material_h, (win_cols - 14) / 2 + 1, "-------------");
                    mvwprintw(win, 6 + raw_material_h - cur_material_h + 1, 
                    (win_cols - 14) / 2 + 1, _ingredients[ingredients_index]->get_name().c_str());
                }
                else
                {
                    mvwprintw(win, 6, (win_cols - 14) / 2 + 1,
                         _ingredients[ingredients_index]->get_name().c_str());
                }
                ++ingredients_index;
            }
        }

        wrefresh(win);
        schedule += "#";
    }
    wrefresh(win);
    // 显示结束信息
    std::string text = "Please press any key to exit!";
    mvwprintw(win, win_rows - 2, (win_cols - text.size()) / 2, text.c_str());
    wrefresh(win); // 刷新窗口以显示文本
    wgetch(win);
    
    delwin(win); // 删除新窗口
    endwin();   // 关闭窗口
}

std::vector< std::shared_ptr<Ingredient> >& EspressoBased::get_ingredients() 
{ 
    return _ingredients;
}

void EspressoBased::operator=(const EspressoBased& esp)
{
    _name = esp._name;
    _ingredients = esp._ingredients;
}