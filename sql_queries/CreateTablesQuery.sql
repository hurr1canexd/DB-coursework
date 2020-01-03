USE newDB -- DB name
GO

IF OBJECT_ID('Ingredients') IS NOT NULL DROP TABLE Ingredients;
GO
IF OBJECT_ID('Recipes') IS NOT NULL DROP TABLE Recipes;
GO
IF OBJECT_ID('Users') IS NOT NULL DROP TABLE Users;
GO
IF OBJECT_ID('Logs') IS NOT NULL DROP TABLE Logs;
GO
IF OBJECT_ID('Comments') IS NOT NULL DROP TABLE Comments;
GO


--dbo.Ingredients
--�����������
CREATE TABLE Ingredients(
	IngrdientID int IDENTITY(1,1) PRIMARY KEY,  -- IDENTITY(seed , increment)
	IngredientName VARCHAR(255),
	Quantity VARCHAR(20)
)
GO


-- �������
CREATE TABLE Recipes(
	RecipeID INT IDENTITY(1,1) PRIMARY KEY,
	RecipeName VARCHAR(30),
	Category VARCHAR(30),
	Cuisine VARCHAR(30),
	Calorie FLOAT,
	RecipeDescription VARCHAR(1000)
)
GO

-- ����� (� ������: ����� (��������� �������), ����� (��� ��� ����� ���������/�������/������������� �������), 
-- ������� ���� (����� ������������� �������)
CREATE TABLE Users(
	UserID INT IDENTITY(1,1) PRIMARY KEY,
	Login VARCHAR(50) NOT NULL,
    Password varchar(100) NOT NULL
)
GO

-- ���� (������ �������� ������)
CREATE TABLE Logs(
	LogID INT IDENTITY(1,1) PRIMARY KEY,
	LogTime TIME,
	Msg VARCHAR(255),
	UserID INT NOT NULL
)
GO

-- ����������� � ��������
CREATE TABLE Comments(
	CommentID INT IDENTITY(1,1) PRIMARY KEY,
	CommentTime TIME,
	Msg VARCHAR(255),
	UserID INT NOT NULL
)
GO
