<%@page import="com.dao.JobDao"%>
<%@page import="com.DB.DBConnect"%>
<%@page import="com.entity.Jobs"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<link rel="icon" type="image/x-icon" href="/favicon.ico">
<title>edir job</title>
<%@ include file="all_component/all_css.jsp" %>
</head>
<body>
<%@include file="all_component/navbar.jsp" %>
<c:if test="${userobj.role ne 'admin' }">
<c:redirect url="login.jsp"></c:redirect>
</c:if>
<%
int id= Integer.parseInt(request.getParameter("id"));
JobDao dao=new JobDao(DBConnect.getConnection());
Jobs job = dao.getJobByID(id);

%>

<form action="update_job" method="post">
<input type="hidden" value="<%= job.getId() %>" name="id">
  <div class="form-group">
    <label for="exampleFormControlInput1">title</label>
    <input type="text" name="title" value="<%=job.getTitle() %>" class="form-control" id="exampleFormControlInput1" placeholder="title">
  </div>
  <div class="form-group">
    <label for="exampleFormControlSelect1">category</label>
    <select class="form-control" name="category" id="exampleFormControlSelect1">
     <option value="<%=job.getCategory() %>"><%=job.getCategory() %></option>
      <option>cat1</option>
      <option>cat2</option>
      <option>cat3</option>
      <option>cat4</option>
      <option>cat5</option>
    </select>
  </div>

  <div class="form-group">
    <label for="exampleFormControlSelect1">status</label>
    <select class="form-control" name="status" id="exampleFormControlSelect1">
    <option value="<%=job.getStatus() %>"><%=job.getStatus() %></option>
      <option>Active</option>
      <option>Inactive</option>
    </select>
  </div>

  <div class="form-group">
    <label for="exampleFormControlSelect1">location</label>
    <select class="form-control" name="location" id="exampleFormControlSelect1">
    <option value="<%=job.getLocation() %>"><%=job.getLocation() %></option>
      <option>Pune</option>
      <option>Mumbai</option>
    </select>
  </div>


  <div class="form-group">
    <label for="exampleFormControlTextarea1">description</label>
    <textarea class="form-control" name="description" id="exampleFormControlTextarea1" rows="3"><%= job.getDescription() %></textarea>
  </div>
  <button type="submit" class="btn btn-primary">Submit</button>
</form>


<%@include file="all_component/footer.jsp" %>
</body>
</html>
