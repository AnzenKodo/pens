<%@page import="com.DB.DBConnect"%>
<%@page import="java.sql.Connection"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<link rel="icon" type="image/x-icon" href="/favicon.ico">
<title>FreelanceFinder: Find Freelance Job that you Like</title>
<%@ include file="all_component/all_css.jsp" %>
<style type="text/css">
.back-img{
	background: linear-gradient(rgba(0, 0, 0, 0.5), rgba(0, 0, 0, 0.2)), url("img/1.png");
	width:100%;
	height:86vh;
	background-repeat: no-repeat;
	background-size: cover;
}
</style>
</head>
<body>
<%@include file="all_component/navbar.jsp" %>

<% Connection conn =DBConnect.getConnection();
//out.println(conn);
%>

<div class="container-fluid back-img">
	<div class="text-center" style="padding-top: 37rem;">
		<h1 class="text-white" style="font-size: 3rem; font-weight: bold;" >
			<i class="fa fa-briefcase" aria-hidden="true"></i> FreelanceFinder
		</h1>
		<p class="text-white" style="font-size: 2rem; margin-top: 0;">Find Freelance Job that you Like</p>
	</div>
</div>

<%@include file="all_component/footer.jsp" %>
</body>
</html>
