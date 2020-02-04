#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // меняю ui главного окна
    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("Кулинарная книга");
    ui->setupUi(this);

    if (!is_first_authorization)
        fillUi();

    //connect(this->ui->categories_comboBox, SIGNAL(currentIndexChanged(int)), this->ui->recipes_listView, SLOT(update());
}


void MainWindow::authorization()
{
    authDlg = new AuthorizationDialog(this);
    authDlg->setDatabase(database);
    authDlg->setModal(true);

    this->setFocusProxy(authDlg);
    connect(authDlg, SIGNAL(autorizationOk(User)), this, SLOT(startClientWork(User)));
    authDlg->show();
}

void MainWindow::setStandart()
{
    ui->userLabel->setText("---");
    ui->categories_comboBox->clear();
    ui->recipe_textEdit->clear();
}

void MainWindow::addRecipe()
{
    addRecDlg = new AddRecipeDialog(this);
    addRecDlg->setDatabase(database);
    addRecDlg->setUserId(user_id);
//    addRecDlg->setModal(true);
    addRecDlg->show();
}

void MainWindow::buildTree()
{
    qDebug() << user_id;
    categories = database->queryGetUniqueCategories(user_id);

    qDebug() << "size " << categories.size();

    ui->categories_comboBox->addItems(categories);


    /*
        QStandardItemModel *model = new QStandardItemModel(); // Создание модели
        for (int i = 0; i < categories.size(); i++) {
        qDebug() << i << categories[i];
        nodes.push_back(new QStandardItem(categories.at(i))); // Создаём узлы
        //nodes[i]->setFlags(nodes[i]->flags() & ~Qt::ItemIsEditable); // Отключаем редактирование узлов
        model->appendRow(nodes[i]); // Добавляем в модель узлы

        QList<QString> recipes = database->GetRecipesByCategory(user_id, categories[i]);

        for (int j = 0; j < recipes.size(); j++) {
            QStandardItem *item = new QStandardItem(recipes.at(i));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            nodes[i]->appendRow(item);
        }
    }*/


    //ui->recipes_treeWidget->
//    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);

//    // QTreeWidgetItem::setText(int column, const QString & text)
//    treeItem->setText(0, name);
//    treeItem->setText(1, description);
//    addTreeChild(treeItem, name + "A", "Child_first");
//    addTreeChild(treeItem, name + "B", "Child_second");
}

void MainWindow::setUserId(int _user_id)
{
    user_id = _user_id;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete database;
}

void MainWindow::startClientWork(User user)
{
    this->ui->userLabel->setText(user.getLogin());
}

void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox::about(this, "Помощь", "Книга кулинарных рецептов");
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, "О программе", "Программа была слеплена одним загадочным студентом МАТИ =)");
}


void MainWindow::on_action_enter_triggered()
{
    setStandart();
    authorization();

}

void MainWindow::on_show_add_recipe_dlg_Btn_clicked()
{
    addRecipe();
}

void MainWindow::fillUi()
{
//    qDebug() << "Я вызвался до авторизации с user_id =" << user_id;
    this->ui->userLabel->setText(database->queryGetLoginById(user_id));
    buildTree();
}

void MainWindow::on_action_backup_triggered()
{
    database->queryCreateBackup("C:\\Users\\tatyana");
}

void MainWindow::on_show_recipes_Btn_clicked()
{
/*    QString category = ui->categories_comboBox->currentText();
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query;
    try {
        query.prepare("EXEC dbo.GetRecipeNamesByCategory ?, ?");
        query.bindValue(0, user_id);
        query.bindValue(1, category);
        query.exec();

//        while (query.next()) {
//             qDebug() << query.value(0);
//             QString name = query.value(0).toString();
//             recipes_list.push_back(name);
//        }
    } catch (...) {
        qDebug() << "Error in queryGetRecipesByCategory";
    }
    model->setQuery(query);
    ui->recipes_listView->setModel(model);
*/
    qDebug() << ui->categories_comboBox->currentText();
    QStringList lst = database->queryGetRecipeNamesByCategory(user_id, ui->categories_comboBox->currentText());
    QStringListModel *model = new QStringListModel;
    model->setStringList(lst);
//    model->flags() & ~Qt::ItemIsEditable
    ui->recipes_listView->setModel(model);

//    for (QString str: lst)
//        ui->recipes_listView->setModel(model);
}

void MainWindow::on_show_cur_recipe_Btn_clicked()
{
    QString cur_category = ui->categories_comboBox->currentText();
    QModelIndex cur_index = ui->recipes_listView->currentIndex();
    QString item_text = cur_index.data(Qt::DisplayRole).toString();
    qDebug() << item_text;

    QString str = database->queryGetIngredientsByName(user_id, item_text, cur_category) +
            database->queryGetRecipeByName(user_id, item_text, cur_category);

    ui->recipe_textEdit->setText(str);

}

void MainWindow::on_del_Btn_clicked()
{
    QString cur_category = ui->categories_comboBox->currentText();
    QModelIndex cur_index = ui->recipes_listView->currentIndex();
    QString item_text = cur_index.data(Qt::DisplayRole).toString();

}
