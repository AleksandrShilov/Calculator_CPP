#include "graph.h"

#include "ui_graph.h"

my::Graph::Graph(QWidget *parent, QString function)
    : QDialog(parent), ui_(new Ui::Graph) {
  ui_->setupUi(this);
  this->function_ = function;
}

my::Graph::~Graph() { delete ui_; }

void my::Graph::on_pushButton_clicked() {
  QString x_input = ui_->line_x->text();
  QString y_input = ui_->line_y->text();

  if (x_input.size() > 0 && y_input.size() > 0) {
    int err_flag = 0;
    int x_val = 0;
    int y_val = 0;
    for (int i = 0; i < x_input.length() - 1; i++) {
      if (x_input.data()[i] < '0' || x_input.data()[i] > '9') {
        err_flag = 1;
        break;
      }
    }

    for (int i = 0; i < x_input.length() - 1; i++) {
      if (y_input.data()[i] < '0' || y_input.data()[i] > '9') {
        err_flag = 1;
        break;
      }
    }

    if (err_flag == 0) {
      x_val = x_input.toInt();
      y_val = y_input.toInt();
    } else {
      ui_->line_x->setText("");
      ui_->line_y->setText("");
    }

    ui_->widget->xAxis->setRange(-1 * x_val, x_val);
    ui_->widget->yAxis->setRange(-1 * y_val, y_val);

    h_ = 0.01;

    for (X_ = -x_val; X_ <= x_val; X_ += h_) {
      char *str;
      x_.push_back(X_);
      QByteArray arr = this->function_.toLocal8Bit();
      str = arr.data();

      Y_ = controller_->Calc(str, X_);

      if (Y_ == y_val) {
        Y_ = -y_val;
      } else if (Y_ == -y_val) {
        Y_ = y_val;
      }

      y_.push_back(Y_);
    }

    ui_->widget->addGraph();
    ui_->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui_->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    ui_->widget->graph(0)->addData(x_, y_);
    ui_->widget->replot();
  }
  ui_->line_x->setText("");
  ui_->line_y->setText("");
}
