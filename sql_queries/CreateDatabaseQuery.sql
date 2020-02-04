CREATE DATABASE Cookbook;
GO

USE Cookbook; -- DB name
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


-- юзеры
CREATE TABLE Users(
	UserID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
	Login VARCHAR(50) NOT NULL,
    Password VARCHAR(100) NOT NULL,
	AccessLevel TINYINT NOT NULL
);
GO

ALTER TABLE Users WITH CHECK 
   ADD CONSTRAINT UQ_Users_Login UNIQUE (Login)

-- рецепты
CREATE TABLE Recipes(
	RecipeID INT IDENTITY(1,1) PRIMARY KEY,
	RecipeName VARCHAR(30),
	Category VARCHAR(30),
	Calorie INT, -- сделать проверку на 0
	RecipeDescription VARCHAR(MAX),
	CookingTime INT, -- до 300
	--AddTime TIME,

	UserID INT FOREIGN KEY (UserID) REFERENCES Users(UserID),

	CONSTRAINT CH_Calorie_Recipes CHECK(Calorie >= 0)
);
GO


--ингредиенты
CREATE TABLE Ingredients(
	IngredientID int IDENTITY(1,1) PRIMARY KEY,  -- IDENTITY(seed , increment)
	IngredientName VARCHAR(50)
);
GO


-- комментарии к рецептам
CREATE TABLE Comments(
	CommentID INT IDENTITY(1,1) PRIMARY KEY,
	CommentTime TIME,
	Msg VARCHAR(255),

	RecipeID INT FOREIGN KEY (RecipeID) REFERENCES Recipes(RecipeID)
);
GO


-- логи (журнал действий юзеров)
CREATE TABLE Logs(
	LogID INT IDENTITY(1,1) PRIMARY KEY,
	UserID INT,
	Msg VARCHAR(255),
	LogTime DATETIME,
	Login VARCHAR(50),
	
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);
GO


-- многие ко многим
CREATE TABLE RecipesIngredients
(
    RecipeID INT CONSTRAINT toRecipeID NOT NULL FOREIGN KEY (RecipeID) REFERENCES Recipes(RecipeID)
        ON DELETE CASCADE,
    IngredientID INT CONSTRAINT toIngredientID NOT NULL FOREIGN KEY (IngredientID) REFERENCES Ingredients(IngredientID)
		ON DELETE CASCADE,

	CONSTRAINT toCrossID PRIMARY KEY CLUSTERED (RecipeID, IngredientID),
	Quantity VARCHAR(20)
);