<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
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

<%--<c:if test="${not empty succMsg}">
	<h4 class="text-center text-danger">${succMsg}</h4>
	<c:remove var="succMsg" />
	</c:if>
 	 --%>
<form action="login" method="post">
  <div class="form-group">
    <label for="exampleInputEmail1">Email address</label>
    <input type="email" class="form-control" name="email" id="exampleInputEmail1" aria-describedby="emailHelp" placeholder="Enter email">
    <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
  </div>
  <div class="form-group">
    <label for="exampleInputPassword1">Password</label>
    <input type="password" name="password" class="form-control" id="exampleInputPassword1" placeholder="Password">
  </div>
  <div class="form-check">
    <input type="checkbox" class="form-check-input" id="exampleCheck1">
    <label class="form-check-label" for="exampleCheck1">Check me out</label>
  </div>
  <button type="submit" class="btn btn-primary">Submit</button>
</form>

<%@include file="all_component/footer.jsp" %>
</body>
</html>
