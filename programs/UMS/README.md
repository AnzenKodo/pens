# User Management System

Java Swing-based desktop application that allows the user to Add, View, Edit,
and Delete user records using a user-friendly form and table.

## Building and Running Application

- Open terminal in current Directory
- Run following command to compile & run:
    - Windows:
        ```cmd
        build.bat
        ```

## Implemented Features

- [x] Table
    - [x] Displays all stored user records.
    - [x] Clicking on a row populates the form with that user’s details for editing or deleting.
- [x] Expected
    - [x] Add user details via form
    - [x] Edit existing user by selecting row in the table
    - [x] Delete user record from list
    - [x] Clear form fields using the Clear button
    - [x] Store user data temporarily in an ArrayList<User>
- [x] Validation
    - [x] All fields must be filled
    - [x] Email should follow a valid format (e.g., abc@example.com)
    - [x] Username must be unique
- [ ] Enhancements
    - [ ] Add a search/filter bar above the table
    - [x] Confirmation dialog before deleting a record
    - [x] Export user list to CSV
- [x] Connect to DB
    - [x] Limit  email & name length to 100
    - [x] Username length to 50
    - [x] Email should be unique
- [ ] README.txt with:
    - [ ] UI Screenshot
    - [x] How to compile and run the application
