#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

class Cords
{
    double x;
    double y;

public:
    Cords()
    {
        this->x = 0;
        this->y = 0;
    }
    Cords(double x, double y):
    x(x), y(y)
    {}
    double get_x()
    {
        return this->x; 
    }
    double get_y()
    {
        return this->y; 
    }
    void print_cods()
    {
        cout << "x: " << this->x << " and y: " << this->y << endl;
    }
    void set_x(double x)
    {
        this->x = x;
    }
    void set_y(double y)
    {
        this->y = y;
    }
};

class Ball
{
    int diameter;
    Cords coordinates;

    friend void re_transformXY();
public:
    Ball() {}
    Ball(double diameter, Cords cords)
    : diameter(diameter), coordinates(cords)
    {}
    void print_ball_stats()
    {
        cout << "Ball diameter is " << this->diameter << endl;
        cout << "Cords are ";
        this->coordinates.print_cods();
    }
    double get_xcord()
    {
        return this->coordinates.get_x();
    }
    double get_ycord()
    {
        return this->coordinates.get_y();
    }
    void set_xcord(double num_x)
    {
        this->coordinates.set_x(num_x);
    }
    void set_ycord(double num_y)
    {
        this->coordinates.set_y(num_y);
    }
    int get_diameter()
    {
        return this->diameter;
    }
};

class Table
{
    Cords A;
    Cords B;
    Cords C;
    Cords D;

    double AB_CD;
    double AD_BC;

    double vector_min;
    double vector_max;

    double up_border;
    double down_border;
    double left_border;
    double right_border;
public:
    Table() {}
    Table(Cords a, Cords b, Cords c, Cords d):
    A(a), B(b), C(c), D(d)
    {
        int x;
        int y;
        x = this->B.get_x() - this->A.get_x();
        y = this->B.get_y() - this->A.get_y();
        this->AB_CD = sqrt(x * x + y * y);
        y = this->D.get_y() - this->A.get_y();
        x = this->D.get_x() - this->A.get_x();
        this->AD_BC = sqrt(x * x + y * y);
        if(AB_CD > AD_BC)
        {
            this->vector_min = AB_CD / 10;
            this->vector_max = (AB_CD * 3) / 10;
        }else{
            this->vector_min = AD_BC / 10;
            this->vector_max = (AD_BC * 3) / 10;
        }
        this->up_border = c.get_y();
        this->down_border = a.get_y();
        this->left_border = a.get_x();
        this->right_border = c.get_x();
    }
    Table(Cords a, Cords c):
    A(a), C(c)
    {
        this->D.set_x(this->A.get_x());
        this->D.set_y(this->C.get_y());
        this->B.set_x(this->C.get_x());
        this->B.set_y(this->A.get_y());

        int x;
        int y;
        x = this->B.get_x() - this->A.get_x();
        y = this->B.get_y() - this->A.get_y();
        this->AB_CD = sqrt(x * x + y * y);
        y = this->D.get_y() - this->A.get_y();
        x = this->D.get_x() - this->A.get_x();
        this->AD_BC = sqrt(x * x + y * y);

        if(AB_CD > AD_BC)
        {
            this->vector_min = AB_CD / 10;
            this->vector_max = (AB_CD * 3) / 10;
        }else{
            this->vector_min = AD_BC / 10;
            this->vector_max = (AD_BC * 3) / 10;
        }

        this->up_border = c.get_y();
        this->down_border = a.get_y();
        this->left_border = a.get_x();
        this->right_border = c.get_x();
    }
    void print_abcd_tp()
    {
        cout << "A is with "; 
        this->A.print_cods();
        cout << "B is with "; 
        this->B.print_cods();
        cout << "C is with "; 
        this->C.print_cods();
        cout << "D is with "; 
        this->D.print_cods();
    }
    double get_vector_min()
    {
        return this->vector_min;
    }
    double get_vector_max()
    {
        return this->vector_max;
    }
    double get_AB_CD()
    {
        return AB_CD;
    }
    void smaller_dim_table_byRad(int radius)
    {
        this->down_border += radius;
        this->up_border -= radius;
        this->left_border += radius;
        this->right_border -= radius;
    }
    double get_up_border()
    {
        return this->up_border;
    }
    double get_down_border()
    {
        return this->down_border;
    }
    double get_left_border()
    {
        return this->left_border;
    }
    double get_right_border()
    {
        return this->right_border;
    }
};

class Vector
{
    Cords starting_cords;
    Cords file_cords;
    Cords arrow_cords;
    int power;

    double vector_lenght;
    double diff_x;
    double diff_y;
public:
    Vector() {}
    Vector(Cords ballCords, Cords arrow_cords, double power)
    : starting_cords(ballCords), file_cords(ballCords), arrow_cords(arrow_cords)
    {
        if(power >= 2 && power <= 5)
        {
            this->power = power;
        }else{
            throw "Wrong power in the start!";
        }
        this->diff_x = this->arrow_cords.get_x() - this->starting_cords.get_x();
        cout << "diff_x " << this->diff_x << endl;
        // cout << this->diff_x << endl;
        this->diff_y = this->arrow_cords.get_y() - this->starting_cords.get_y();
        // cout << this->diff_y << endl;
        vector_lenght = sqrt(this->diff_x * this->diff_x + this->diff_y * this->diff_y);
    }
    double get_vector_lenght()
    {
        return this->vector_lenght;
    }
    int get_power()
    {
        return this->power;
    }
    double get_diff_x()
    {
        return this->diff_x;
    }
    double get_diff_y()
    {
        return this->diff_y;
    }
    void set_arrow_cordsX(double x)
    {
        this->arrow_cords.set_x(x);
    }
    void set_arrow_cordsY(double y)
    {
        this->arrow_cords.set_y(y);
    }
    double get_arrow_cordsX()
    {
        return this->arrow_cords.get_x();
    }
    double get_arrow_cordsY()
    {
        return this->arrow_cords.get_y();
    }
    void set_diff_x(double diff)
    {
        this->diff_x = diff;
    }
    void set_diff_y(double diff)
    {
        this->diff_y = diff;
    }
    double get_startcord_x()
    {
        return this->starting_cords.get_x();
    }
    double get_startcord_y()
    {
        return this->starting_cords.get_y();
    }
    double get_filecord_x()
    {
        return this->file_cords.get_x();
    }
    double get_filecord_y()
    {
        return this->file_cords.get_y();
    }
    void set_startcord_x(double x)
    {
        this->starting_cords.set_x(x);
    }
    void set_startcord_y(double y)
    {
        this->starting_cords.set_y(y);
    }
    void set_power(int a)
    {
        this->power = a;
    }
    void set_lenght(double a)
    {
        this->vector_lenght = a;
    }
};

void moving_ball(Ball* ball, Vector* vector)
{
    for(int i = 0; i < vector->get_power(); i++)
    {
        ball->set_xcord(ball->get_xcord() + vector->get_diff_x());
        ball->set_ycord(ball->get_ycord() + vector->get_diff_y());
    }
}

void re_transformXY(double& x_new, double& y_new, double angle, double x_A, double y_A)
{
    double x_copy = x_new;
    x_new = (x_new - x_A) * cos(angle) + (y_new - y_A) * sin(angle);
    y_new = (y_new - y_A) * cos(angle) - (x_copy - x_A) * sin(angle);
}

void moving_ball_onTable(Ball* ball, Vector* vector, Table* table, int swapped, double angle, double xA, double yA)
{
    table->smaller_dim_table_byRad(ball->get_diameter() / 2);
    for(int i = 0; i < vector->get_power(); i++)
    {
        // ball->set_xcord(ball->get_xcord() + vector->get_diff_x());
        // ball->set_ycord(ball->get_ycord() + vector->get_diff_y());
        // vector->set_arrow_cordsX(vector->get_arrow_cordsX() + vector->get_diff_x());
        // vector->set_arrow_cordsY(vector->);
        // cout << "First check - ball_xcord: " << ball->get_xcord() << " vector_diff_x: " << vector->get_diff_x() << endl;
        Cords contact;
        if(ball->get_ycord() + vector->get_diff_y() > table->get_up_border())
        {
            double need_once = table->get_up_border() - (ball->get_ycord() + vector->get_diff_y());
            contact.set_y(table->get_up_border());
            contact.set_x((vector->get_startcord_x() - vector->get_arrow_cordsX()) * (contact.get_y() - vector->get_arrow_cordsY()) / (vector->get_startcord_y() - vector->get_arrow_cordsY()) + vector->get_arrow_cordsX());
            if(swapped == 1)
            {
                double x = contact.get_x();
                double y = contact.get_y();
                re_transformXY(x, y, angle, xA, yA);
                contact.set_x(x);
                contact.set_y(y);
            }
            cout << "1 case: The ball bounced into the wall (" << contact.get_x() << ", "<< contact.get_y() << ")" << endl;
            // cout << "ball_xcord: " << ball->get_xcord() << " vector_diff_x: " << vector->get_diff_x() << endl;
            ball->set_xcord(ball->get_xcord() + vector->get_diff_x());
            ball->set_ycord(table->get_up_border() - need_once);
            if(contact.get_x() == table->get_left_border() || contact.get_x() == table->get_right_border())
            {
                cout << "That's the corner, ball is returned to the starting position!" << endl;
                ball->set_xcord(vector->get_filecord_x());
                ball->set_ycord(vector->get_filecord_y());
                return;
            }

            vector->set_diff_y(-vector->get_diff_y());
            vector->set_startcord_x(ball->get_xcord());
            vector->set_startcord_y(ball->get_ycord());
            vector->set_arrow_cordsX(vector->get_startcord_x() + vector->get_diff_x());
            vector->set_arrow_cordsY(vector->get_startcord_y() + vector->get_diff_y());
            continue;
        }
        if(ball->get_ycord() + vector->get_diff_y() < table->get_down_border())
        {
            double need_once = table->get_down_border() - (ball->get_ycord() + vector->get_diff_y());
            contact.set_y(table->get_down_border());
            contact.set_x((vector->get_startcord_x() - vector->get_arrow_cordsX()) * (contact.get_y() - vector->get_arrow_cordsY()) / (vector->get_startcord_y() - vector->get_arrow_cordsY()) + vector->get_arrow_cordsX());
            if(swapped == 1)
            {
                double x = contact.get_x();
                double y = contact.get_y();
                re_transformXY(x, y, angle, xA, yA);
                contact.set_x(x);
                contact.set_y(y);
            }
            cout << "2 case: The ball bounced into the wall (" << contact.get_x() << ", "<< contact.get_y() << ")" << endl;
            // cout << "ball_xcord: " << ball->get_xcord() << " vector_diff_x: " << vector->get_diff_x() << endl;
            ball->set_xcord(ball->get_xcord() + vector->get_diff_x());
            ball->set_ycord(table->get_down_border() + need_once);

            if(contact.get_x() == table->get_left_border() || contact.get_x() == table->get_right_border())
            {
                cout << "That's the corner, ball is returned to the starting position!" << endl;
                ball->set_xcord(vector->get_filecord_x());
                ball->set_ycord(vector->get_filecord_y());
                return;
            }
            vector->set_diff_y(-vector->get_diff_y());
            vector->set_startcord_x(ball->get_xcord());
            vector->set_startcord_y(ball->get_ycord());
            vector->set_arrow_cordsX(vector->get_startcord_x() + vector->get_diff_x());
            vector->set_arrow_cordsY(vector->get_startcord_y() + vector->get_diff_y());
            continue;
        }
        if(ball->get_xcord() + vector->get_diff_x() < table->get_left_border())
        {
            double need_once = table->get_left_border() - (ball->get_xcord() + vector->get_diff_x());
            contact.set_x(table->get_left_border());
            contact.set_y((vector->get_startcord_y() - vector->get_arrow_cordsY()) * (contact.get_x() - vector->get_arrow_cordsX()) / (vector->get_startcord_x() - vector->get_arrow_cordsX()) + vector->get_arrow_cordsY());
            if(swapped == 1)
            {
                double x = contact.get_x();
                double y = contact.get_y();
                re_transformXY(x, y, angle, xA, yA);
                contact.set_x(x);
                contact.set_y(y);
            }
            cout << "3 case: The ball bounced into the wall (" << contact.get_x() << ", "<< contact.get_y() << ")" << endl;
            // cout << "ball_xcord: " << ball->get_xcord() << " vector_diff_x: " << vector->get_diff_x() << endl;
            ball->set_xcord(table->get_left_border() + need_once);
            ball->set_ycord(ball->get_ycord() + vector->get_diff_y());
            if(contact.get_y() == table->get_down_border() || contact.get_y() == table->get_up_border())
            {
                cout << "That's the corner, ball is returned to the starting position!" << endl;
                ball->set_xcord(vector->get_filecord_x());
                ball->set_ycord(vector->get_filecord_y());
                return;
            }

            vector->set_diff_x(-vector->get_diff_x());
            vector->set_startcord_x(ball->get_xcord());
            vector->set_startcord_y(ball->get_ycord());
            vector->set_arrow_cordsX(vector->get_startcord_x() + vector->get_diff_x());
            vector->set_arrow_cordsY(vector->get_startcord_y() + vector->get_diff_y());
            continue;
        }
        if(ball->get_xcord() + vector->get_diff_x() > table->get_right_border())
        {
            double need_once = table->get_right_border() - (ball->get_xcord() + vector->get_diff_x());
            contact.set_x(table->get_right_border());
            contact.set_y((vector->get_startcord_y() - vector->get_arrow_cordsY()) * (contact.get_x() - vector->get_arrow_cordsX()) / (vector->get_startcord_x() - vector->get_arrow_cordsX()) + vector->get_arrow_cordsY());
            if(swapped == 1)
            {
                double x = contact.get_x();
                double y = contact.get_y();
                re_transformXY(x, y, angle, xA, yA);
                contact.set_x(x);
                contact.set_y(y);
            }
            cout << "4 case: The ball bounced into the wall (" << contact.get_x() << ", "<< contact.get_y() << ")" << endl;
            // cout << "ball_xcord: " << ball->get_xcord() << " vector_diff_x: " << vector->get_diff_x() << endl;
            ball->set_xcord(table->get_left_border() - need_once);
            ball->set_ycord(ball->get_ycord() + vector->get_diff_y());
            if(contact.get_y() == table->get_down_border() || contact.get_y() == table->get_up_border())
            {
                cout << "That's the corner, ball is returned to the starting position!" << endl;
                ball->set_xcord(vector->get_filecord_x());
                ball->set_ycord(vector->get_filecord_y());
                return;
            }

            vector->set_diff_x(-vector->get_diff_x());
            vector->set_startcord_x(ball->get_xcord());
            vector->set_startcord_y(ball->get_ycord());
            vector->set_arrow_cordsX(vector->get_startcord_x() + vector->get_diff_x());
            vector->set_arrow_cordsY(vector->get_startcord_y() + vector->get_diff_y());
            continue;
        }
        ball->set_xcord(ball->get_xcord() + vector->get_diff_x());
        ball->set_ycord(ball->get_ycord() + vector->get_diff_y());
    }
    if(swapped == 1)
    {
        double x = ball->get_xcord();
        double y = ball->get_ycord();
        re_transformXY(x, y, angle, xA, yA);
        ball->set_xcord(x);
        ball->set_ycord(y);
    }
    cout << ball->get_xcord() << " " << ball->get_ycord() << endl;
}

void transformXY(double& x_prev, double& y_prev, double angle, double x_A, double y_A)
{
    double x_copy = x_prev;
    x_prev = x_prev * cos(angle) - y_prev * sin(angle) + x_A;
    y_prev = x_copy * sin(angle) + y_prev * cos(angle) + y_A;
}

int main()
{
    // Cords a = Cords(0, 0);
    // Cords b = Cords(320, 0);
    // Cords c = Cords(320, 160);
    // Cords d = Cords(0, 160);
    // Table check = Table(a, b, c, d);
    // check.print_abcd_tp();
    try
    {
        int swapped = 0;
        ifstream stats("stats.txt");

        double angle;
        Ball ball;
        Vector vector_ball;
        Table check;
        double xA, yA;
        double xA1, xB, xC, xD;
        double yA1, yB, yC, yD;
        stats >> xA >> yA;
        stats >> xB >> yB;
        if(yA != yB)
        {
            swapped = 1;
            double my_x = xB-xA;
            double my_y = yB-yA;
            angle = atan2(my_y, my_x);
            cout << "Angle - " << angle * (180.0 / 3.14159258) << endl;
        }
        if(swapped == 1)
        {
            xA1 = xA;
            yA1 = yA;
            transformXY(xA1, yA1, angle, xA, yA);
            Cords a = Cords(xA1, yA1);
            transformXY(xB, yB, angle, xA, yA);
            Cords b = Cords(xB, yB);
            stats >> xC >> yC;
            transformXY(xC, yC, angle, xA, yA);
            Cords c = Cords(xC, yC);
            stats >> xD >> yD;
            transformXY(xD, yD, angle, xA, yA);
            Cords d = Cords(xD, yD);
            check = Table(a, b, c, d);
            //cout << check.get_vector_min() << " " << check.get_vector_max() << endl;
            double diameter;
            double x, y;
            stats >> diameter >> x >> y;
            transformXY(x, y, angle, xA, yA);
            Cords ball_cords = Cords(x, y);
            ball = Ball(diameter, ball_cords);
            //ball.print_ball_stats();
            int power;
            stats >> power >> x >> y;
            transformXY(x, y, angle, xA, yA);
            Cords vec = Cords(x, y);
            //vec.print_cods();
            vector_ball = Vector(ball_cords, vec, power);
            // cout << vector_ball.get_vector_lenght() << endl;
            if(vector_ball.get_vector_lenght() < check.get_vector_min())
            {
                throw "Too shord\n";
            }
            if(vector_ball.get_vector_lenght() > check.get_vector_max())
            {
                throw "Too long!\n";
            }
        } else {
            Cords a = Cords(xA, yA);
            Cords b = Cords(xB, yB);
            stats >> xC >> yC;
            Cords c = Cords(xC, yC);
            stats >> xD >> yD;
            Cords d = Cords(xD, yD);
            check = Table(a, b, c, d);
            //cout << check.get_vector_min() << " " << check.get_vector_max() << endl;
            double diameter;
            double x, y;
            stats >> diameter >> x >> y;
            Cords ball_cords = Cords(x, y);
            ball = Ball(diameter, ball_cords);
            //ball.print_ball_stats();
            int power;
            stats >> power >> x >> y;
            Cords vec = Cords(x, y);
            //vec.print_cods();
            vector_ball = Vector(ball_cords, vec, power);
            // cout << vector_ball.get_vector_lenght() << endl;
            if(vector_ball.get_vector_lenght() < check.get_vector_min() || vector_ball.get_vector_lenght() > check.get_vector_max())
            {
                throw "Vector lenght in the start is incorrect!\n";
            }
        }
        stats.close();

        // check.print_abcd_tp();

        // ball.print_ball_stats();
        // moving_ball(&ball, &vector_ball);
        // ball.print_ball_stats();
        while(1)
        {
            moving_ball_onTable(&ball, &vector_ball, &check, swapped, angle, xA, yA);
            int a;
            double b, c;
            cout << "Now you can hit the ball: / power / X / Y /\n";
            cin >> a >> b >> c;
            vector_ball.set_arrow_cordsX(b);
            vector_ball.set_arrow_cordsY(c);
            vector_ball.set_power(a);
            vector_ball.set_diff_x(vector_ball.get_arrow_cordsX() - vector_ball.get_startcord_x());
            vector_ball.set_diff_y(vector_ball.get_arrow_cordsY() - vector_ball.get_startcord_y());
            vector_ball.set_lenght(sqrt(vector_ball.get_diff_x() * vector_ball.get_diff_x() + vector_ball.get_diff_y() * vector_ball.get_diff_y()));
            while(vector_ball.get_vector_lenght() < check.get_vector_min() || vector_ball.get_vector_lenght() > check.get_vector_max() || a < 2 || a > 5)
            {
                cout << "Vector lenght is incorrect!\n";
                cout << "Go again: / power / X / Y /\n";
                cin >> a >> b >> c;
                vector_ball.set_arrow_cordsX(b);
                vector_ball.set_arrow_cordsY(c);
                vector_ball.set_power(a);
                vector_ball.set_diff_x(vector_ball.get_arrow_cordsX() - vector_ball.get_startcord_x());
                vector_ball.set_diff_y(vector_ball.get_arrow_cordsY() - vector_ball.get_startcord_y());
                vector_ball.set_lenght(sqrt(vector_ball.get_diff_x() * vector_ball.get_diff_x() + vector_ball.get_diff_y() * vector_ball.get_diff_y()));
            }
        }

    }catch(const char* err){
        cout << err;
    }
    return 0;
}
