#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_abs, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_ac, SIGNAL(released()), this, SLOT(ac_pressed()));
    connect(ui->pushButton_acos, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_asin, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_atan, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_acosh, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_asinh, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_atanh, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_ans, SIGNAL(released()), this, SLOT(ans_pressed()));
    connect(ui->pushButton_arg, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_conj, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_cos, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_cosh, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_del, SIGNAL(released()), this, SLOT(delete_1_char_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_dot, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_enter_arg, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_enter_cart, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_equal, SIGNAL(released()), this, SLOT(equal_pressed()));
    connect(ui->pushButton_exp, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_imag, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_left_brac, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_ln, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_log, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_num0, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num1, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num2, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num3, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num4, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num5, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num6, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num7, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num8, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_num9, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_pow, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_proj, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_real, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_right_brac, SIGNAL(released()), this, SLOT(operatr_pressed()));
    connect(ui->pushButton_sin, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_sinh, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_sqrt, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_tan, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_tanh, SIGNAL(released()), this, SLOT(numeric_button_pressed()));
    connect(ui->pushButton_input_deg_rad, SIGNAL(released()), this, SLOT(iodg_pressed()));
    connect(ui->pushButton_output_deg_rad, SIGNAL(released()), this, SLOT(iopc_pressed()));
    connect(ui->pushButton_unary_minus, SIGNAL(released()), this, SLOT(unary_minus_pressed()));
    connect(ui->pushButton_pi, SIGNAL(released()), this, SLOT(operatr_pressed()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

//show the last answer
void MainWindow::ans_pressed() {
    ui->label_display->setText(ans);
}

//select degree or radian
void MainWindow::iodg_pressed() {
    QPushButton *button=static_cast<QPushButton*>(sender());
    if (button->isChecked()) {
        button->setText("Deg");
        ui->label_angl->setText("Angle: Degree");
    } else {
        button->setText("Rad");
        ui->label_angl->setText("Angle: Radian");
    }
}

//select polar or cartesian
void MainWindow::iopc_pressed() {
    QPushButton *button=static_cast<QPushButton*>(sender());
    if (button->isChecked()) {
        button->setText("Polar");
        ui->label_disp->setText("Display: Polar");
    } else {
        button->setText("Cart");
        ui->label_disp->setText("Display: Cartesian");
    }
}
void MainWindow::operatr_pressed() {
    QPushButton *button=static_cast<QPushButton*>(sender());
    QRegExp re("\\d*");
    QString entered=ui->label_display->text()+button->text();
    ui->label_display->setText(entered);
}

//for button with operater exactly same as its labeled text
void MainWindow::numeric_button_pressed() {
    QPushButton *button=static_cast<QPushButton*>(sender());
    QRegExp re("\\d*");
    QString entered=ui->label_display->text()+button->text();
    if (!re.exactMatch(button->text())) {
        entered+="(";
    }
    ui->label_display->setText(entered);
}

//just need to delete one char
void MainWindow::delete_1_char_pressed() {
    QString entered=ui->label_display->text();
    if (entered.length()>0) {
        entered=entered.left(entered.length()-1);
    }
    ui->label_display->setText(entered);
}

//clear
void MainWindow::ac_pressed() {
    ui->label_display->setText("");
}

//effect of unary operator
void MainWindow::unary_minus_pressed() {
    std::string entered=(ui->label_display->text()).toStdString();
    std::string lastNum="";
    size_t curr=entered.length()-1;
    //progress until hit the first operator from end of string and read in last number
    while ((curr!=std::string::npos) && (entered[curr]=='9' || entered[curr]=='8' || entered[curr]=='7' || entered[curr]=='6' || entered[curr]=='5' ||
           entered[curr]=='4' || entered[curr]=='3' || entered[curr]=='2' || entered[curr]=='1' || entered[curr]=='0' ||
           entered[curr]=='.')) {
        lastNum=lastNum+entered[curr];
        entered=entered.substr(0, entered.length()-1);
        curr--;
    }
    std::reverse(lastNum.begin(), lastNum.end());
    //add - to last number
    if (entered[curr]=='-') {
        entered=entered.substr(0, entered.length()-1);
    } else {
        lastNum="-"+lastNum;
    }
    entered+=lastNum;
    ui->label_display->setText(QString::fromStdString(entered));
}

//when enter pressed, clean up entered expression
void MainWindow::equal_pressed() {
    QString entered=ui->label_display->text();
    QString processed_ent;
    std::complex<double> result;
    std::string output;
    std::string real_str;
    std::string imag_str;
    std::string arg_str;
    std::string norm_str;
    std::string argrad_str;
    double real_pt;
    double imag_pt;
    double arg;
    double argrad;
    double nrm;
    bool pure_r;
    bool pure_im;
    //check if expression is valid
    if (entered=="ecse202") {
        ui->label_display->setText("In the name of Prof. Ferrie, see you in DPM!");
        return;
    } else if (entered=="ecse210") {
        ui->label_display->setText("In memory of Prof. Davis, see you in hydro quebec!");
        return;
    } else if (!checkValid(entered)) {
        ui->label_display->setText("error");
        return;
    }
    processed_ent=replaceSym(entered);
#ifdef DEBUG
    qDebug()<<processed_ent;
#endif
    std::string str(processed_ent.toStdString());
    //calculate expression based on degree/radian
    try {
        result=calculate(str, ui->pushButton_input_deg_rad->isChecked());
    } catch (char const *ex) {
        ui->label_display->setText(ex);
        ui->label_display->setText("error");
        return;
    }
    //read in result parameters
    real_pt=std::real(result);
    imag_pt=std::imag(result);
    arg=(std::arg(result)*180)/3.14159265358979323846;
    argrad=std::arg(result);
    nrm=std::abs(result);
    real_str=(removeLastZero(std::to_string(real_pt)));
    imag_str=(removeLastZero(std::to_string(imag_pt)));
    arg_str=(removeLastZero(std::to_string(arg)));
    norm_str=(removeLastZero(std::to_string(nrm)));
    argrad_str=(removeLastZero(std::to_string(argrad)));
    //compare 0 with torelance of double precision
    pure_r=(imag_str=="-0" || imag_str=="0" || std::abs(imag_pt)<1.0e-13);
    pure_im=(real_str=="-0" || real_str=="0" || std::abs(real_pt)<1.0e-13);
#ifdef DEBUG
    qDebug()<<real_pt;
    qDebug()<<imag_pt;
#endif
    //generate approperate output according to user setting cart/polar
    if (ui->pushButton_output_deg_rad->isChecked()) {
        if (pure_r==true) {
            output=real_str;
        } else {
            if (ui->pushButton_input_deg_rad->isChecked()) {
                output=norm_str+"∠"+arg_str;
            } else {
                output=norm_str+"∠"+argrad_str;
            }
        }
    } else {
        if (pure_im==true) {
            output=imag_str+"j";
        } else if (pure_r==true) {
            output=real_str;
        } else {
            output=real_str+"+"+imag_str+"j";
        }
    }
    //save to ans
    ans=QString::fromStdString(output);
    ui->label_display->setText(ans);
}
