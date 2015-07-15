A = zeros(2000,2);
for i=1:40;
    file = sprintf('Spin20_%d',i);
    B = importdata(file);
    A(:,2) = A(:,2)+B(:,2);
end

A(:,1) = B(:,1);
A(:,2) = A(:,2)/40;

p = polyfit(A(:,1),A(:,2),2);
    