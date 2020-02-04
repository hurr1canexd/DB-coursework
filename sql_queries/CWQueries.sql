USE Cookbook; -- database name
GO


/*
	PROC Registration
*/
IF OBJECT_ID('Registration', 'P') IS NOT NULL DROP PROC Registration;
GO
CREATE PROC Registration @Login AS VARCHAR(50), @Password AS VARCHAR(100), @AccessLevel AS TINYINT
AS
	IF NOT EXISTS (SELECT * FROM Users WHERE @Login = Login)
	BEGIN
		INSERT INTO Users VALUES (@Login, @Password, 1)
		SELECT 1
	END;
	ELSE SELECT 0
GO


/*
	PROC Authorize
*/
IF OBJECT_ID('Authorize', 'P') IS NOT NULL DROP PROC Authorize;
GO
CREATE PROC Authorize @Login AS VARCHAR(50), @Password AS VARCHAR(100)
AS
	IF EXISTS (SELECT * FROM Users WHERE @Login = Login and @Password = Password)
		SELECT UserID FROM Users where @Login = Login
	ELSE SELECT -1
GO


/*
	PROC GetLoginById
*/
IF OBJECT_ID('GetLoginById', 'P') IS NOT NULL DROP PROC GetLoginById;
GO
CREATE PROC GetLoginById @UserID AS INT
AS
	IF EXISTS (SELECT * FROM Users WHERE @UserID = UserID)
		SELECT Login FROM Users where @UserID = UserID
	ELSE SELECT -1
GO


/*
	PROC AddRecipe
*/
IF OBJECT_ID('AddRecipe', 'P') IS NOT NULL DROP PROC AddRecipe;
GO
CREATE PROC AddRecipe
@RecipeName AS VARCHAR(30),
@Category AS VARCHAR(30),
@Calorie AS INT,
@RecipeDescription AS VARCHAR(MAX),
@CookingTime AS INT,
@UserID AS INT
AS
	IF EXISTS (SELECT * FROM Users WHERE UserID = @UserID) AND 
	NOT EXISTS (SELECT * FROM Recipes WHERE RecipeName = @RecipeName AND Category = @Category)
	BEGIN
		INSERT INTO Recipes (RecipeName, Category, Calorie, RecipeDescription, CookingTime, UserID) 
		VALUES (@RecipeName, @Category, @Calorie, @RecipeDescription, @CookingTime, @UserID);
		
		SELECT RecipeID FROM Recipes
		WHERE RecipeName = @RecipeName AND Category = @Category
	END
	ELSE SELECT -1
GO


/*
	PROC AddIngredient
*/
IF OBJECT_ID('AddIngredient', 'P') IS NOT NULL DROP PROC AddIngredient;
GO
CREATE PROC AddIngredient
@RecipeID AS INT,
@IngredientName AS VARCHAR(30),
@Quantity AS VARCHAR(20)
AS
	IF NOT EXISTS (SELECT * FROM Ingredients WHERE @IngredientName = IngredientName)
	BEGIN
		INSERT INTO Ingredients (IngredientName) 
		VALUES (@IngredientName);
	END

	DECLARE @SelectedIngredientID INT
	SELECT @SelectedIngredientID = IngredientID FROM Ingredients WHERE @IngredientName = IngredientName

	INSERT INTO RecipesIngredients (RecipeID, IngredientID, Quantity) 
	VALUES (@RecipeID, @SelectedIngredientID, @Quantity);
GO


/*
PROC GetUniqueCategories
*/
IF OBJECT_ID('GetUniqueCategories', 'P') IS NOT NULL DROP PROC GetUniqueCategories;
GO
CREATE PROC GetUniqueCategories
@UserID AS INT
AS
	SELECT DISTINCT Category FROM Recipes
	WHERE UserID = @UserID
GO


/*
	PROC GetRecipeNamesByCategory
*/
IF OBJECT_ID('GetRecipeNamesByCategory', 'P') IS NOT NULL DROP PROC GetRecipeNamesByCategory;
GO
CREATE PROC GetRecipeNamesByCategory
@UserID AS INT,
@Category AS VARCHAR(30)
AS
	IF EXISTS (SELECT * FROM Recipes WHERE @UserID = UserID AND @Category = Category)
	BEGIN
		SELECT RecipeName FROM Recipes 
		WHERE Category = @Category AND UserID = @UserID
	END
GO


/*
	PROC GetRecipeByName
*/
IF OBJECT_ID('GetRecipeByName', 'P') IS NOT NULL DROP PROC GetRecipeByName;
GO
CREATE PROC GetRecipeByName
@UserID AS INT,
@RecipeName AS VARCHAR(30),
@Category AS VARCHAR(30)
AS
	IF EXISTS (SELECT * FROM Recipes WHERE @UserID = UserID AND @Category = Category)
	BEGIN
		SELECT Calorie, CookingTime, RecipeDescription FROM Recipes 
		WHERE Category = @Category AND @RecipeName = RecipeName AND UserID = @UserID 
	END
	ELSE SELECT '', 0, ''
GO


/*
	FUNCTION GetIngredientById
*/
IF OBJECT_ID('GetIngredientById') IS NOT NULL DROP FUNCTION GetIngredientById;
GO
CREATE FUNCTION GetIngredientById
(@IngredientID AS INT)
RETURNS VARCHAR(50)
AS
BEGIN
	DECLARE @SelectedIngredientName VARCHAR(50);
	SELECT @SelectedIngredientName = IngredientName FROM Ingredients
	WHERE @IngredientID = IngredientID
	RETURN @SelectedIngredientName
END
GO


/*
	PROC GetIngredientsByName
*/
IF OBJECT_ID('GetIngredientsByName', 'P') IS NOT NULL DROP PROC GetIngredientsByName;
GO
CREATE PROC GetIngredientsByName
@UserID AS INT,
@RecipeName AS VARCHAR(30),
@Category AS VARCHAR(30)
AS
	DECLARE @SelectedRecipeID INT	
	SELECT @SelectedRecipeID = RecipeID FROM Recipes 
	WHERE @RecipeName = RecipeName AND @UserID = UserID AND @Category = Category

	SELECT dbo.GetIngredientById(IngredientID), Quantity FROM RecipesIngredients
	WHERE @SelectedRecipeID = RecipeID
GO


/*
	PROC CreateBackup
*/
IF OBJECT_ID('CreateBackup', 'P') IS NOT NULL DROP PROC CreateBackup;
GO
CREATE PROC CreateBackup
@Path AS VARCHAR(200)
AS
    BACKUP DATABASE Cookbook TO DISK = @Path
	WITH NAME = 'Full Backup of MyDB';
GO


/*
	TRIGGERS
*/
IF OBJECT_ID('RecordAdding', 'TR') IS NOT NULL DROP TRIGGER RecordAdding;
GO
CREATE TRIGGER RecordAdding ON Users
AFTER INSERT
AS
BEGIN
	INSERT INTO Logs
	(UserID, Msg, LogTime, Login)
	SELECT i.UserID, 'Добавлен пользователь', GETDATE(), i.Login
	FROM Users t 
	INNER JOIN inserted i ON t.UserID=i.UserID 
END
GO


IF OBJECT_ID('RecordDeleting', 'TR') IS NOT NULL DROP TRIGGER RecordDeleting;
GO
CREATE TRIGGER RecordDeleting ON Users
AFTER UPDATE
AS
BEGIN
	INSERT INTO Logs
	(UserID, Msg, LogTime, Login)
	SELECT i.UserID, 'Удалён пользователь', GETDATE(), i.Login
	FROM Users t 
	INNER JOIN deleted i ON t.UserID=i.UserID 
END
GO
