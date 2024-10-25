<%@page import="com.DB.DBConnect"%>
<%@page import="com.dao.JobDao"%>
<%@page import="com.entity.Jobs"%>
<%@page import="java.util.List" %>
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
<% JobDao dao=new JobDao(DBConnect.getConnection());
List<Jobs> jlist = dao.getAllJobs();
for(Jobs j:jlist) {%>

	<div class="card" style="width: 18rem;">

  <div class="card-body">
    <h5 class="card-title"> <%=j.getTitle() %></h5>
    <p class="card-text"><%=j.getDescription() %></p>
    <p class="card-text"><%=j.getCategory() %></p>
    <p class="card-text"><%=j.getStatus() %></p>
    <!--<p class="card-text"><%=j.getPdate() %></p>-->
    <a href="edit_job.jsp?id=<%=j.getId() %>" class="btn btn-primary">Edit</a>
    <a href="delete_job?id=<%=j.getId() %>" class="btn btn-primary">Delete</a>
  </div>
</div>
<%} %>

<%@include file="all_component/footer.jsp" %>
</body>
</html>
