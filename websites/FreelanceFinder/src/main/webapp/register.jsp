<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<!DOCTYPE html>
<html>
<head>
<link rel="icon" type="image/x-icon" href="/favicon.ico">
<meta charset="ISO-8859-1">
<title>Login Page</title>
<%@ include file="all_component/all_css.jsp" %>
</head>
<body>
<%@include file="all_component/navbar.jsp" %>

<form action="register" method="post">
  <div class="form-group">
    <label for="exampleFormControlInput1">name</label>
    <input type="text" name="name" class="form-control" id="exampleFormControlInput1" placeholder="name">
  </div>

  <div class="form-group">
    <label for="exampleFormControlInput1">email</label>
    <input type="text" name="email" class="form-control" id="exampleFormControlInput1" placeholder="email">
  </div>

  <div class="form-group">
    <label for="exampleFormControlInput1">password</label>
    <input type="password" name="password" class="form-control" id="exampleFormControlInput1" placeholder="password">
  </div>

  <div class="form-group">
    <label for="exampleFormControlInput1">qualification</label>
    <input type="text" name="qualification" class="form-control" id="exampleFormControlInput1" placeholder="qualification">
  </div>

  <button type="submit" class="btn btn-primary">Submit</button>
</form>

<%@include file="all_component/footer.jsp" %>
</body>
</html>
