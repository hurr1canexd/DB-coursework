#include "addrecipedialog.h"
#include "ui_addrecipedialog.h"

AddRecipeDialog::AddRecipeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipeDialog)
{

//    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("Добавление рецепта");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); // делаю окно нересайзбл
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint); // удаляю знак вопроса из title bar'a

    ui->setupUi(this);

    ui->ingredients_tableWidget->setHorizontalHeaderLabels(QStringList{"Название ингредиента", "Количество"});
    ui->ingredients_tableWidget->resizeColumnsToContents();
}


void AddRecipeDialog::setDatabase(Database *db)
{
    database = db;
}

void AddRecipeDialog::setUserId(int _user_id)
{
    user_id = _user_id;
}


AddRecipeDialog::~AddRecipeDialog()
{
    delete ui;
}

void AddRecipeDialog::on_add_recipe_Btn_clicked()
{
    // TODO: ограничить нормально ввод в textedit
    if (ui->recipe_description_textEdit->toPlainText().length() > 15000) {
        QMessageBox::warning(this, "Ошибка", "Вы превысили допустимое количество символов (15000)!!!");
        return;
    }

//    ui->add_recipe_Btn->setDisabled(true);

    getDataFromUi();

    if (recipe_name.isEmpty() || category.isEmpty() || recipe_description.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Недостаточно информации о рецепте");
        return;
    }
    recipe_id = database->queryAddRecipe(recipe_name, category, calorie, recipe_description, cooking_time, user_id);
    if (recipe_id == -1) {
        QMessageBox::critical(this, "Ошибка", "Рецепт с таким именем в данной категории уже есть");
        return;
    }
    qDebug() << recipe_id;

    qDebug();
    qDebug();
    for (int i = 0; i < ui->ingredients_tableWidget->rowCount(); i++) {
        if (ui->ingredients_tableWidget->item(i, 0)) {
            qDebug() << i << ":" << ui->ingredients_tableWidget->item(i, 0)->text();
            database->queryAddIngredient(recipe_id,
                                         ui->ingredients_tableWidget->item(i, 0)->text().trimmed(),
                                         ui->ingredients_tableWidget->item(i, 1)->text().trimmed());
        }
    }

    QMessageBox::about(this, "Ура", "Вы успешно добавили рецепт");
    this->close();
}

void AddRecipeDialog::getDataFromUi()
{
    recipe_name = ui->recipe_name_lineEdit->text().trimmed();
    category = ui->recipe_category_lineEdit->text().trimmed();
    calorie = ui->calorie_spinBox->value();
    recipe_description = ui->recipe_description_textEdit->toPlainText();
    cooking_time = ui->cooking_time_spinBox->value();
}

void AddRecipeDialog::on_plus_Btn_clicked()
{
    ui->ingredients_tableWidget->insertRow(ui->ingredients_tableWidget->rowCount());
}

void AddRecipeDialog::on_minus_Btn_clicked()
{
    ui->ingredients_tableWidget->removeRow(ui->ingredients_tableWidget->rowCount() - 1);
}
