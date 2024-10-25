<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
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
<c:if test="${userobj.role ne 'admin' }">
<c:redirect url="login.jsp"></c:redirect>
</c:if>

	<h1>Welcome admin</h1>
<%@include file="all_component/footer.jsp" %>
</body>
</html>
