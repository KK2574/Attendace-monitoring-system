const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const Attendance = require('./models/Attendance');

const app = express();
app.use(cors());
app.use(express.json());

mongoose.connect('mongodb://localhost:27017/fingerprint-attendance', {
  useNewUrlParser: true,
  useUnifiedTopology: true,
}).then(() => console.log('MongoDB Connected'))
  .catch((err) => console.log('MongoDB Connection Error:', err));

// GET attendance
app.get('/api/attendance', async (req, res) => {
  const data = await Attendance.find();
  res.json(data);
});

// ✅ POST attendance
app.post('/api/attendance', async (req, res) => {
  const { fingerprintId } = req.body;

  if (!fingerprintId) {
    return res.status(400).json({ error: "Fingerprint ID is required" });
  }

  try {
    const newAttendance = new Attendance({ fingerprintId });
    await newAttendance.save();
    res.status(201).json({ message: "Attendance stored" });
  } catch (err) {
    res.status(500).json({ error: "Failed to store attendance" });
  }
});

const PORT = 3000;
app.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`));
