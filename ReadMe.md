# Qt Firebase Authentication Example

This is an example project demonstrating how to connect a Qt application with a Firebase Realtime Database using REST API for authentication.

## Setup

Create a new Firebase project in the Firebase Console.<br>
In the project dashboard, navigate to Database in the left sidebar.<br>
Create a new Firebase Realtime Database by clicking on Create database.<br>
Choose the Start in test mode option and click on Enable.<br>
From the Rules tab, set the read and write rules to true to allow unauthenticated access to the database:<br>

	json

	{
	  "rules": {
	    ".read": true,
	    ".write": true
	  }
	}

In the project settings, go to the Service Accounts tab and click on Generate new private key to download a JSON file containing your Firebase project credentials.<br>
Rename the downloaded JSON file to firebase.json and place it in the root directory of your Qt project.

## Building and Running the Project

Open the project in Qt Creator.<br>
Build the project.<br>
Run the project.

## Usage
Creating a New User<br>

To create a new user, enter the email address and password in the respective fields and click on Create Account button. If the account is successfully created, a message box will be displayed indicating the same.

## Logging In

To log in, enter the email address and password in the respective fields and click on Log In button. If the login is successful, a message box will be displayed indicating the same.<br>

Note: The email address and password entered for authentication are sent to the Firebase Realtime Database for verification. If they match with the records in the database, the authentication is successful. Otherwise, it fails.

## Contributing

Contributions are welcome! If you find any issues or would like to suggest new features, please submit a pull request or open an issue.

# References

[Google Firebase REST API Documentation](https://firebase.google.com/docs/reference/rest/database)<br>
[Qt Documentation](https://doc.qt.io/)<br>
[Firebase Website](https://firebase.google.com/)<br>
